#include "../../include/Database.h"
#include <iostream>
#include <pqxx/pqxx>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Database::Database(const std::string& connection_conf)
    : connection_conf_(connection_conf)
{
    checkDatabase();
}

void Database::checkDatabase()
{
    try // подключение к postgres для проверки существует ли БД и если нет, то создать её
    {
        BOOST_LOG_TRIVIAL(info) << "Check if a database exists";

        pqxx::connection connection_to_db_(connection_conf_);

        if(connection_to_db_.is_open())
        {
            pqxx::work check_db_(connection_to_db_);
            pqxx::result result_check_db_ = check_db_.exec("SELECT datname FROM pg_database WHERE datname = 'WorkLineDatabase';");

            if(!result_check_db_.empty())
            {
                BOOST_LOG_TRIVIAL(info) << "Database found";

            }
            else
            {
                BOOST_LOG_TRIVIAL(info) << "Database not found";

            }

            check_db_.commit();
        }
        connection_to_db_.close();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

Database::~Database()
{}
