#include "../include/Database.h"
#include "../include/Server.h"
#include <boost/asio/io_context.hpp>
#include <boost/log/utility/setup.hpp>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/keywords/auto_flush.hpp>

int main()
{
    boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%", boost::log::keywords::auto_flush = true);
    boost::log::add_common_attributes();

    boost::asio::io_context io_context;

    boost::asio::io_context::work work(io_context);

    std::string conninfo_to_postgres = "dbname=postgres user=admin password=15900512 hostaddr=127.0.0.1";
    std::string conninfo_to_worklinedatabase = "dbname=worklinedatabase user=admin password=15900512 hostaddr=127.0.0.1";

    Database db(io_context, conninfo_to_postgres, conninfo_to_worklinedatabase);

    Server server(io_context);

    io_context.run();

    return 0;
}
