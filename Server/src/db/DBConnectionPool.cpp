#include "../../include/DBConnectionPool.h"

DBConnectionPool::DBConnectionPool(const std::string& conninfo_to_worklinedatabase_, const int poolSize_)
    : conninfo_to_worklinedatabase_(conninfo_to_worklinedatabase_)
{
    for(int i = 0; i < poolSize_; ++i)
    {
        std::shared_ptr<DBConnection> connection_(std::make_shared<DBConnection>(conninfo_to_worklinedatabase_));
        connection_->connect();
        connectionPool_.push(connection_);
    }
}

DBConnectionPool::~DBConnectionPool()
{}

std::shared_ptr<DBConnection> DBConnectionPool::getConnection()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(connectionPool_.empty())
    {
        return std::make_shared<DBConnection>(conninfo_to_worklinedatabase_);
    }

    auto connection_ = connectionPool_.front();
    connectionPool_.pop();

    return connection_;
}

void DBConnectionPool::returnConnection(std::shared_ptr<DBConnection> connection_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    connectionPool_.push(connection_);
}
