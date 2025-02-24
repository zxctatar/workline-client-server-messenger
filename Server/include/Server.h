#ifndef SERVER_H
#define SERVER_H

#include "DBConnectionPool.h"
#include "ConnectedUsers.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio.hpp>

class Server{

public:
    explicit Server(boost::asio::io_context& io_context);
    ~Server();

private:
    void do_accept();

    std::string conninfo_to_worklinedatabase;
    DBConnectionPool connectionPool_;
    boost::asio::thread_pool threadPool_;
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    ConnectedUsers connectedUsers_;
};

#endif // SERVER_H
