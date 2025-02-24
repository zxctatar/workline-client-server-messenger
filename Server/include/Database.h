#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <boost/asio/io_context.hpp>
#include "DBConnection.h"

class Database
{
public:
    explicit Database(boost::asio::io_context& io_context, std::string& conninfo_to_postgres, std::string& conninfo_to_worklinedatabase);
    ~Database();

private:
    void initializing();

    void createDatabase(pqxx::connection& connection_to_db_);
    void createUsers(pqxx::connection& connection_to_db_);
    void createTables(pqxx::connection& connection_to_worklinedatabase_);
    void setPrivileges(pqxx::connection& connection_to_db_);
    void createTrigger(pqxx::connection& connection_to_worklinedatabase_);
    void insertAdmin(pqxx::connection& connection_to_worklinedatabase_);

    boost::asio::io_context& io_context_;
    std::string conninfo_to_postgres_;
    std::string conninfo_to_worklinedatabase_;
};

#endif // DATABASE_H
