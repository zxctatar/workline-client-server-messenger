#include "../../include/RequestRouter.h"
#include "../../include/Session.h"
#include <memory>
#include <iostream>

RequestRouter::RequestRouter()
{
}

RequestRouter::~RequestRouter()
{
}

void RequestRouter::defineQuery(const boost::asio::any_io_executor& executor_, const int userID_, const nlohmann::json& json_, DBConnectionPool& connectionPool_, std::weak_ptr<Session> session_, ConnectedUsers& connUsers_)
{
    if(json_["Info"] == "GET_ID")
    {
        std::string responseJson_ = jsonWorker_.createUserIdJson(userID_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            //do read везде
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Registration")
    {
        if(!json_.contains("lastname") || !json_.contains("firstname") ||
           !json_.contains("middlename") || !json_.contains("login") ||
           !json_.contains("phonenumber") || !json_.contains("email") ||
           !json_.contains("password"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string lastname_ = json_["lastname"].get<std::string>();
        std::string firstname_ = json_["firstname"].get<std::string>();
        std::string middlename_ = json_["middlename"].get<std::string>();
        std::string login_ = json_["login"].get<std::string>();
        long long int phonenumber_ = std::stoll(json_["phonenumber"].get<std::string>());
        std::string email_ = json_["email"].get<std::string>();
        std::string password_ = json_["password"].get<std::string>();

        std::string response_ = userManager_.regUser(connection_, lastname_, firstname_, middlename_, login_, phonenumber_, email_, password_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createRegistrationCodeJson(response_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Login")
    {
        if(!json_.contains("login") || !json_.contains("password"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string login_ = json_["login"].get<std::string>();
        std::string password_ = json_["password"].get<std::string>();

        LoginResult response_ = userManager_.loginUser(connection_, login_, password_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_;

        if(response_.code_ != "ACCESS_ALLOWED_USER" && response_.code_ != "ACCESS_ALLOWED_ADMIN")
        {
            responseJson_ = jsonWorker_.createLoginUnsuccessJson(response_.code_);
        }
        else
        {
            if(response_.userRole_ == "admin")
            {
                connUsers_.addAuthorizeAdmin(response_.userID_, session_);
            }
            else
            {
                connUsers_.addAuthorizeUser(response_.userID_, session_);
            }
            responseJson_ = jsonWorker_.createLoginSuccessJson(response_.code_, response_.userID_, response_.userRole_);
        }

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
            //session_->do_read();
        });
    }
    else if(json_["Info"] == "Add_Server")
    {
        if(!json_.contains("serverName") || !json_.contains("serverDescription"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string serverName_ = json_["serverName"].get<std::string>();
        std::string serverDescription_ = json_["serverDescription"].get<std::string>();

        AddResult response_ = serverManager_.addServer(connection_, serverName_, serverDescription_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_;

        if(response_.code_ == "SERVER_ADDED")
        {
            responseJson_ = jsonWorker_.createAddingServerSuccessJson(response_.code_, response_.serverID_, response_.serverName_, response_.serverDescription_);

            boost::asio::post(executor_, [this, session_, &connUsers_, responseJson_](){
                for(const auto& i : connUsers_.getAuthorizeAdmin())
                {
                    i.second.lock()->do_write(responseJson_);
                }
            });
        }
        else
        {
            responseJson_ = jsonWorker_.createAddingServerUnsuccessJson(response_.code_);

            boost::asio::post(executor_, [this, session_, responseJson_](){
                session_.lock()->do_write(responseJson_);
            });
        }
    }
    else if(json_["Info"] == "Get_Servers")
    {
        auto connection_ = connectionPool_.getConnection();
        std::vector<ServerStruct> response_ = serverManager_.getServers(connection_, userID_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetServersJson(response_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else
    {
    }
}

