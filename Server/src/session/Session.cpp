#include "../../include/Session.h"
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Session::Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_)
    : io_context_(io_context_)
    , socket_(std::move(socket_))
    , connectedUsers_(connectedUsers_)
    , user_id_(0)
{
}

void Session::setAccountId(const int id_)
{
    user_id_ = id_;

    send_id(jsonWorker_.createUserIdJson(user_id_));
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    std::cout << "user_id_ = " << user_id_ << std::endl;
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, 1024),
                            [this, self](boost::system::error_code ec, std::size_t lenght)
                            {
                                if(!ec)
                                {
                                    do_read();
                                }
                            });
}

void Session::send_id(const std::string& jsonMessageID_)
{
    auto self(shared_from_this());

    // Преобразуем длину сообщения в сетевой порядок байт (big-endian)
    uint32_t length = htonl(jsonMessageID_.size());

    // Создаем буфер, который сначала содержит длину, а затем сами данные
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(&length, sizeof(length)));
    buffers.push_back(boost::asio::buffer(jsonMessageID_));

    boost::asio::async_write(socket_, buffers, [this, self](const boost::system::error_code ec_, std::size_t bytes_transferred){
        if(ec_)
        {
            BOOST_LOG_TRIVIAL(error) << ec_.message();
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Sent the id to the client";
        }
    });
}

void Session::do_write()
{

}

Session::~Session()
{}
