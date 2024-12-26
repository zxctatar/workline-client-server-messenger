#include "../include/Database.h"
#include <boost/asio/io_context.hpp>
#include <boost/log/utility/setup.hpp>
#include <iostream>

int main()
{
    boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%");
    boost::log::add_common_attributes();

    boost::asio::io_context io_context;
    boost::asio::io_context::work work(io_context);

    // const std::string connection_conf("dbname=postgres user=admin password=15900512 hostaddr=127.0.0.1");

    // Database db(connection_conf);

    return 0;
}
