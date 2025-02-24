#include "../../include/Session.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Session::Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_, boost::asio::thread_pool& threadPool_, DBConnectionPool& connectionPool_)
    : connectionPool_(connectionPool_)
    , threadPool_(threadPool_)
    , io_context_(io_context_)
    , socket_(std::move(socket_))
    , connectedUsers_(connectedUsers_)
    , userID_(0)
    , isAutorized(false)
{
}

Session::~Session()
{
    if(isAutorized)
    {
        connectedUsers_.removeAuthorizeUser(userID_);
    }
}

void Session::setAccountId(const int id_)
{
    userID_ = id_;
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());

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
                std::cerr << "Error reading message length: " << ec.message() << "\n";
            }
        });
}

void Session::read_message()
{
    auto self(shared_from_this());

    boost::asio::async_read(socket_, boost::asio::buffer(buffer_),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                std::string request_(buffer_.begin(), buffer_.end());
                nlohmann::json jsonRequest_ = jsonWorker_.parceJson(request_);

                boost::asio::post(threadPool_, [this, self, jsonRequest_](){
                    std::string response_ = requestRouter_.defineQuery(userID_, jsonRequest_, connectionPool_);

                    boost::asio::post(self->socket_.get_executor(), [this, self, response_](){
                        do_write(response_);
                        do_read();
                    });
                });
            }
            else
            {
                std::cerr << "Error reading message: " << ec.message() << "\n";
            }
        });
}

void Session::do_write(const std::string& jsonMessageID_)
{
    auto self_(shared_from_this());

    uint32_t length_ = htonl(jsonMessageID_.size());

    std::vector<boost::asio::const_buffer> buffers_;
    buffers_.push_back(boost::asio::buffer(&length_, sizeof(length_)));
    buffers_.push_back(boost::asio::buffer(jsonMessageID_));

    boost::asio::async_write(socket_, buffers_, [this, self_](const boost::system::error_code ec_, std::size_t bytes_transferred_){
        if(ec_)
        {
            BOOST_LOG_TRIVIAL(error) << ec_.message();
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Sent response to the user";
        }
    });
}
