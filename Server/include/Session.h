#ifndef SESSION_H
#define SESSION_H

#include "ConnectedUsers.h"
#include <memory>
#include <boost/asio/ip/tcp.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_);
    ~Session();

    void start();

private:
    void do_read();
    void do_write();
    void generate_id();

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    ConnectedUsers& connectedUsers_;

    char data_[1024];
};

#endif // SESSION_H
