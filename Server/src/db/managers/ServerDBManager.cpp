#include "../../../include/ServerDBManager.h"
#include "../../../include/DatabaseQueries.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>

ServerDBManager::ServerDBManager()
{
}

ServerDBManager::~ServerDBManager()
{
}

AddResult ServerDBManager::addServer(std::shared_ptr<DBConnection> connection_, const std::string& serverName_, const std::string& serverDescription_) const
{
    AddResult addResult_;

    addResult_.serverName_ = serverName_;
    addResult_.serverDescription_ = serverDescription_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Adding a new server...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work check_server_(connection_->getConnection());
        pqxx::result result_check_server_name_ = DatabaseQueries::checkServerName(check_server_, serverName_);
        check_server_.commit();

        if(result_check_server_name_.empty())
        {
            pqxx::work add_server_(connection_->getConnection());
            pqxx::result result_add_server_ = DatabaseQueries::addNewServer(add_server_, serverName_, serverDescription_);
            add_server_.commit();

            BOOST_LOG_TRIVIAL(info) << "Server addition completed.";

            addResult_.serverID_ = result_add_server_[0][0].as<int>();
            addResult_.code_ = "SERVER_ADDED";

            return addResult_;
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Server with this name already exists.";

            addResult_.code_ = "SERVER_NAME_EXISTS";

            return addResult_;
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        addResult_.code_ = "ERROR";

        return addResult_;
    }
}

std::vector<ServerStruct> ServerDBManager::getServers(std::shared_ptr<DBConnection> connection_, const int userID_) const
{
    std::vector<ServerStruct> servers_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Getting the user's servers...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work check_is_admin_(connection_->getConnection());
        pqxx::result result_check_is_admin_ = DatabaseQueries::checkIsAdmin(check_is_admin_, userID_);
        check_is_admin_.commit();

        bool isAdmin_ = !result_check_is_admin_.empty();

        pqxx::work get_servers_(connection_->getConnection());
        pqxx::result result_get_servers_;

        if(isAdmin_)
        {
            result_get_servers_ = DatabaseQueries::getAllServers(get_servers_);
        }
        else
        {
            result_get_servers_ = DatabaseQueries::getUserServers(get_servers_, userID_);
        }

        get_servers_.commit();

        for(const auto& row : result_get_servers_)
        {
            ServerStruct server_;
            server_.serverID_ = row[0].as<int>();
            server_.serverName_ = row[1].as<std::string>();
            server_.serverDescription_ = row[2].as<std::string>();

            servers_.push_back(server_);
        }

        BOOST_LOG_TRIVIAL(info) << "Servers have been received.";

        return servers_;
    }
    catch (const std::exception& e)
    {
        std::cout << "2" << std::endl;
        BOOST_LOG_TRIVIAL(error) << e.what();
        return servers_;
    }
}

ServerDeleteStruct ServerDBManager::deleteServer(std::shared_ptr<DBConnection> connection_, const int serverId_) const
{
    ServerDeleteStruct serverDeleteStruct_;
    serverDeleteStruct_.serverId_ = serverId_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Delete the server...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work delete_server_(connection_->getConnection());
        pqxx::result result_delete_server_ = DatabaseQueries::deleteServer(delete_server_, serverId_);
        delete_server_.commit();

        if(result_delete_server_.affected_rows() > 0)
        {
            serverDeleteStruct_.code_ = "SERVER_DELETED";
            return serverDeleteStruct_;
        }
        else
        {
            serverDeleteStruct_.code_ = "NOTHING WAS DELETED";
            return serverDeleteStruct_;
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        serverDeleteStruct_.code_ = "ERROR";
        return serverDeleteStruct_;
    }
}




