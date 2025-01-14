#include "../../include/Server.h"
#include "../../include/Session.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Server::Server(boost::asio::io_context& io_context)
    : io_context_(io_context)
    , acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001))
{
    do_accept();
}

void Server::do_accept()
{
    try
    {
        acceptor_.async_accept([this](boost::system::error_code ec_, boost::asio::ip::tcp::socket socket_){
            if(!ec_)
            {
                BOOST_LOG_TRIVIAL(info) << "New connection.";
                std::make_shared<Session>(std::move(socket_));
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << ec_.message();
            }
            do_accept();
        });
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

Server::~Server()
{}
