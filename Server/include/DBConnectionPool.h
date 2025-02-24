#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include <string>
#include <queue>
#include <memory>
#include <mutex>
#include "DBConnection.h"

class DBConnectionPool
{
public:
    explicit DBConnectionPool(const std::string& conninfo_to_worklinedatabase_, const int poolSize_);
    ~DBConnectionPool();

    std::shared_ptr<DBConnection> getConnection();
    void returnConnection(std::shared_ptr<DBConnection> connection_);

private:
    std::queue<std::shared_ptr<DBConnection>> connectionPool_;
    std::mutex mutex_;
    std::string conninfo_to_worklinedatabase_;
};

#endif // DBCONNECTIONPOOL_H
