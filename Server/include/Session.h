#ifndef SESSION_H
#define SESSION_H

#include "ConnectedUsers.h"
#include "JsonWorker.h"
#include "RequestRouter.h"
#include "DBConnectionPool.h"
#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <set>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io_context_, std::set<std::shared_ptr<Session>>& active_sessions_, boost::asio::ip::tcp::socket socket_, ConnectedUsers& connectedUsers_, boost::asio::thread_pool& threadPool_, DBConnectionPool& connectionPool_);
    ~Session();

    void start();
    void setAccountId(const int id_);
    void do_read();
    void do_write(const std::string& jsonMessage_);
    void write_next();

private:
    void read_message();
    void generate_id();
    void stop();

    RequestRouter requestRouter_;
    JsonWorker jsonWorker_;
    DBConnectionPool& connectionPool_;
    boost::asio::thread_pool& threadPool_;
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    ConnectedUsers& connectedUsers_;
    std::set<std::shared_ptr<Session>>& active_sessions_;
    int userID_;
    bool isAutorized;

    std::vector<char> buffer_;
    uint32_t message_size_;
    std::deque<std::string> write_queue_;
};

#endif // SESSION_H
