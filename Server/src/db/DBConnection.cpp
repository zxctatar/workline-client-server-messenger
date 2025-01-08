#include "../../include/DBConnection.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <thread>

DBConnection::DBConnection(boost::asio::io_context& io_context, const std::string& conninfo)
    : reconnect_timer_(std::make_unique<boost::asio::steady_timer>(io_context))
    , io_context_(io_context)
    , conninfo_(conninfo)
    , started_(false)
{
}

void DBConnection::connect()
{
    try
    {
        started_ = true;
        connection_ = std::make_unique<pqxx::connection>(conninfo_);

        if(connection_->is_open())
        {
            BOOST_LOG_TRIVIAL(info) << "Сonnection successful.";
        }
    }
    catch (const pqxx::broken_connection& e)
    {
        throw;
    }
    catch (const std::exception& e)
    {
        throw;
    }
}

void DBConnection::reconnect()
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Аttempting to reconnect to the database server...";
        connection_ = std::make_unique<pqxx::connection>(conninfo_);
        if(connection_->is_open())
        {
            BOOST_LOG_TRIVIAL(info) << "Connection to the database has been restored.";
        }
    }
    catch (const pqxx::broken_connection& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        BOOST_LOG_TRIVIAL(info) << "Reconnecting again in 5 sec...";

        std::this_thread::sleep_for(std::chrono::seconds(5));
        reconnect();
        // reconnect_timer_->expires_after(std::chrono::seconds(5));
        // reconnect_timer_->async_wait([this](const boost::system::error_code& ec){
        //     if(!ec)
        //     {
        //         reconnect();
        //     }
        // });
    }
}

void DBConnection::stop()
{
    if(connection_)
    {
        started_ = false;
        connection_.reset();
        BOOST_LOG_TRIVIAL(info) << "Database connection closed.";
    }
    else
    {
        BOOST_LOG_TRIVIAL(warning) << "Attempt to stop a non-active database connection.";
    }
}

pqxx::connection& DBConnection::getConnection() const
{
    return *connection_;
}

bool DBConnection::isStarted() const
{
    return started_;
}

bool DBConnection::isConnected() const
{
    return connection_ && connection_->is_open();
}

DBConnection::~DBConnection()
{
    if(connection_)
    {
        stop();
    }
}
