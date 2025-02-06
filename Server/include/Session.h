#ifndef SESSION_H
#define SESSION_H

#include "ConnectedUsers.h"
#include "JsonWorker.h"
#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_);
    ~Session();

    void start();
    void setAccountId(const int id_);

private:
    void do_read();
    void do_write();
    void send_id(const std::string& jsonMessageID_);
    void generate_id();

    JsonWorker jsonWorker_;
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    ConnectedUsers& connectedUsers_;
    int user_id_;

    char data_[1024];
};

#endif // SESSION_H
