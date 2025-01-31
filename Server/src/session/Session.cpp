#include "../../include/Session.h"

Session::Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_)
    : io_context_(io_context_)
    , socket_(std::move(socket_))
    , connectedUsers_(connectedUsers_)
{

}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
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

Session::~Session()
{}
