#ifndef SESSION_H
#define SESSION_H

#include "ConnectedUsers.h"
#include "JsonWorker.h"
#include "RequestRouter.h"
#include "DBConnectionPool.h"
#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io_context_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_, boost::asio::thread_pool& threadPool_, DBConnectionPool& connectionPool_);
    ~Session();

    void start();
    void setAccountId(const int id_);

private:
    void do_read();
    void read_message();
    void do_write(const std::string& jsonMessageID_);
    void generate_id();

    RequestRouter requestRouter_;
    JsonWorker jsonWorker_;
    DBConnectionPool& connectionPool_;
    boost::asio::thread_pool& threadPool_;
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    ConnectedUsers& connectedUsers_;
    int userID_;
    bool isAutorized;

    std::vector<char> buffer_;
    uint32_t message_size_;
};

#endif // SESSION_H
