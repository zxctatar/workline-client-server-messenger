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

        std::string receivedLastname_ = json_["lastname"].get<std::string>();
        std::string receivedFirstname_ = json_["firstname"].get<std::string>();
        std::string receivedMiddlename_ = json_["middlename"].get<std::string>();
        std::string receivedLogin_ = json_["login"].get<std::string>();
        long long int receivedPhonenumber_ = std::stoll(json_["phonenumber"].get<std::string>());
        std::string receivedEmail_ = json_["email"].get<std::string>();
        std::string receivedPassword_ = json_["password"].get<std::string>();

        std::string response_ = userManager_.regUser(connection_, receivedLastname_, receivedFirstname_, receivedMiddlename_, receivedLogin_, receivedPhonenumber_, receivedEmail_, receivedPassword_);
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

        std::string receivedLogin_ = json_["login"].get<std::string>();
        std::string receivedPassword_ = json_["password"].get<std::string>();

        LoginResult response_ = userManager_.loginUser(connection_, receivedLogin_, receivedPassword_);
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
            responseJson_ = jsonWorker_.createLoginSuccessJson(response_.code_, response_.userFirstName_, response_.userLastName_, response_.userMiddleName_, response_.userEmail_, response_.userPhoneNumber, response_.userID_, response_.userRole_, response_.userLogin_, response_.userPassword_);
        }

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Add_Server")
    {
        if(!json_.contains("serverName") || !json_.contains("serverDescription"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string receivedServerName_ = json_["serverName"].get<std::string>();
        std::string receivedServerDescription_ = json_["serverDescription"].get<std::string>();

        AddResult response_ = serverManager_.addServer(connection_, receivedServerName_, receivedServerDescription_);
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
    else if(json_["Info"] == "Reconnect")
    {
        if(!json_.contains("login") || !json_.contains("password"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        std::string receivedLogin_ = json_["login"].get<std::string>();
        std::string receivedPassword_ = json_["password"].get<std::string>();

        auto connection_ = connectionPool_.getConnection();
        ReconnectResult response_ = userManager_.reconnectUser(connection_, receivedLogin_, receivedPassword_);
        connectionPool_.returnConnection(connection_);

        if(response_.userRole_ == "user")
        {
            connUsers_.addAuthorizeUser(response_.userID_, session_);
        }
        else if(response_.userRole_ == "admin")
        {
            connUsers_.addAuthorizeAdmin(response_.userID_, session_);
        }
    }
    else if(json_["Info"] == "DeleteServer")
    {
        if(!json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        ServerDeleteStruct serverDeleteStruct_ = serverManager_.deleteServer(connection_, receivedServerId_);
        std::string responseJson_ = jsonWorker_.createDeleteServerJson(serverDeleteStruct_);

        if(serverDeleteStruct_.code_ == "SERVER_DELETED")
        {
            std::vector<int> usersId_ = userManager_.getUsersOnServers(connection_, receivedServerId_);

            boost::asio::post(executor_, [this, &connUsers_, responseJson_, usersId_](){
                for(const auto& i : usersId_)
                {
                    connUsers_.getUser(i).lock()->do_write(responseJson_);
                }
            });
            boost::asio::post(executor_, [this, session_, &connUsers_, responseJson_](){
                for(const auto& i : connUsers_.getAuthorizeAdmin())
                {
                    i.second.lock()->do_write(responseJson_);
                }
            });
        }

        connectionPool_.returnConnection(connection_);
    }
    else if(json_["Info"] == "Get_UnverUsers")
    {
        auto connection_ = connectionPool_.getConnection();
        std::vector<UnverUserStruct> response_ = userManager_.getUnverUsers(connection_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetUnverUsersJson(response_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Approve_User")
    {
        if(!json_.contains("userId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.approveUser(connection_, receivedUserId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJsonForSender_ = jsonWorker_.createApproveUserJson(response_, receivedUserId_);
        std::string reponseJsonForOther_ = jsonWorker_.createDeleteFromUnverUserJson(receivedUserId_);

        boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
            session_.lock()->do_write(responseJsonForSender_);
        });

        if(response_ == "APPROVED")
        {
            boost::asio::post(executor_, [this, session_, reponseJsonForOther_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmin())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }
                    i.second.lock()->do_write(reponseJsonForOther_);
                }
            });
        }
    }
    else if(json_["Info"] == "Reject_User")
    {
        if(!json_.contains("userId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.rejectUser(connection_, receivedUserId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJsonForSender_ = jsonWorker_.createRejectUserJson(response_, receivedUserId_);
        std::string responseJsonForOther_ = jsonWorker_.createDeleteFromUnverUserJson(receivedUserId_);

        boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
            session_.lock()->do_write(responseJsonForSender_);
        });

        if(response_ == "REJECTED")
        {
            boost::asio::post(executor_, [this, session_, responseJsonForOther_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmin())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }
                    i.second.lock()->do_write(responseJsonForOther_);
                }
            });
        }
    }
    else if(json_["Info"] == "Get_Candidate_Users")
    {
        if(!json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::vector<CandidateUserStruct> response_ = userManager_.getCandidateUsers(connection_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createCandidateUsersJson(response_, receivedServerId_);

        boost::asio::post(executor_, [this, responseJson_, session_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Add_User_On_Server")
    {
        if(!json_.contains("serverId") || !json_.contains("userId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.addUserOnServer(connection_, receivedUserId_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJsonForSender_ = jsonWorker_.createUserAddedOnServerJson(response_, receivedUserId_, receivedServerId_);
        std::string responseJsonForOther_ = jsonWorker_.createDeleteUserOnServerJson(receivedUserId_, receivedServerId_);

        boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
            session_.lock()->do_write(responseJsonForSender_);
        });

        if(response_ == "USER_ADDED")
        {
            boost::asio::post(executor_, [this, session_, responseJsonForOther_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmin())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }
                    i.second.lock()->do_write(responseJsonForOther_);
                }
            });
        }
    }
}

