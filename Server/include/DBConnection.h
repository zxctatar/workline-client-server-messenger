#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <string>
#include <pqxx/pqxx>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>

class DBConnection
{
public:
    explicit DBConnection(boost::asio::io_context& io_context, const std::string& conninfo);

    void reconnect();
    void stop();
    pqxx::connection& getConnection() const;
    void connect();
    bool isStarted() const;
    bool isConnected() const;

    ~DBConnection();
private:

    std::unique_ptr<pqxx::connection> connection_;
    std::unique_ptr<boost::asio::steady_timer> reconnect_timer_;
    boost::asio::io_context& io_context_;
    std::string conninfo_;
    bool started_;
};

#endif // DBCONNECTION_H
