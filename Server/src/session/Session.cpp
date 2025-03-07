#include "../../include/Session.h"
#include <thread>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Session::Session(boost::asio::io_context& io_context_, std::set<std::shared_ptr<Session>>& active_sessions_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_, boost::asio::thread_pool& threadPool_, DBConnectionPool& connectionPool_)
    : connectionPool_(connectionPool_)
    , threadPool_(threadPool_)
    , io_context_(io_context_)
    , socket_(std::move(socket_))
    , connectedUsers_(connectedUsers_)
    , active_sessions_(active_sessions_)
    , userID_(0)
    , isAutorized(false)
{
}

Session::~Session()
{
    if(isAutorized)
    {
        connectedUsers_.removeAuthorize(userID_);
    }
}

void Session::setAccountId(const int id_)
{
    userID_ = id_;
    isAutorized = true;
}

void Session::start()
{
    do_read();
}

void Session::stop()
{
    socket_.close();

    auto it = std::find_if(active_sessions_.begin(), active_sessions_.end(),
                           [this](const std::shared_ptr<Session>& s) { return s.get() == this; });

    if (it != active_sessions_.end()) {
        active_sessions_.erase(it);
    }
}

void Session::do_read()
{
    std::weak_ptr self(shared_from_this());

    boost::asio::async_read(socket_, boost::asio::buffer(&message_size_, sizeof(message_size_)),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                message_size_ = ntohl(message_size_);
                buffer_.resize(message_size_);
                read_message();
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << "Error reading message length: " << ec.message();
                stop();
            }
        });
}

void Session::read_message()
{
    std::weak_ptr self(shared_from_this());

    boost::asio::async_read(socket_, boost::asio::buffer(buffer_),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/)
                            {
                                if (!ec)
                                {
                                    std::string request_(buffer_.begin(), buffer_.end());
                                    nlohmann::json jsonRequest_ = jsonWorker_.parceJson(request_);

                                    boost::asio::post(threadPool_, [this, self, jsonRequest_](){
                                        requestRouter_.defineQuery(self.lock()->socket_.get_executor(), userID_, jsonRequest_, connectionPool_, shared_from_this(), connectedUsers_);
                                    });

                                    buffer_.clear();
                                    do_read();
                                }
                                else
                                {
                                    BOOST_LOG_TRIVIAL(error) << "Error reading message: " << ec.message() << "\n";
                                }
                            });
}

void Session::do_write(const std::string& jsonMessage_)
{
    bool write_in_progress = !write_queue_.empty();
    write_queue_.push_back(jsonMessage_);

    if (!write_in_progress) // Только если нет активной отправки
    {
        write_next();
    }
}

void Session::write_next()
{
    if (write_queue_.empty())
        return;

    std::weak_ptr self(shared_from_this());
    uint32_t length_ = htonl(write_queue_.front().size());

    std::vector<boost::asio::const_buffer> buffers_;
    buffers_.push_back(boost::asio::buffer(&length_, sizeof(length_)));
    buffers_.push_back(boost::asio::buffer(write_queue_.front()));

    boost::asio::async_write(socket_, buffers_,
                             [this, self](const boost::system::error_code ec_, std::size_t /*bytes_transferred_*/)
                             {
                                 if (!ec_)
                                 {
                                     write_queue_.pop_front();
                                     if (!write_queue_.empty())  // Если в очереди ещё есть сообщения, отправляем следующее
                                     {
                                         write_next();
                                     }
                                 }
                                 else
                                 {
                                     BOOST_LOG_TRIVIAL(error) << "Write error: " << ec_.message();
                                 }
                             });
}
