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
           !json_.contains("password") || !json_.contains("image") ||
           !json_.contains("birthDate"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::vector<uint8_t> receivedImage_ = imageWorker_.base64_decode(json_["image"].get<std::string>());
        std::string receivedLastname_ = json_["lastname"].get<std::string>();
        std::string receivedFirstname_ = json_["firstname"].get<std::string>();
        std::string receivedMiddlename_ = json_["middlename"].get<std::string>();
        std::string receivedBirthDate_ = json_["birthDate"].get<std::string>();
        std::string receivedLogin_ = json_["login"].get<std::string>();
        long long int receivedPhonenumber_ = std::stoll(json_["phonenumber"].get<std::string>());
        std::string receivedEmail_ = json_["email"].get<std::string>();
        std::string receivedPassword_ = json_["password"].get<std::string>();

        std::string response_ = userManager_.regUser(connection_, receivedImage_, receivedLastname_, receivedFirstname_, receivedMiddlename_, receivedBirthDate_, receivedLogin_, receivedPhonenumber_, receivedEmail_, receivedPassword_);
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
            responseJson_ = jsonWorker_.createLoginSuccessJson(response_.code_, response_.userAvatar_, response_.userBirthDate_, response_.userFirstName_, response_.userLastName_, response_.userMiddleName_, response_.userEmail_, response_.userPhoneNumber, response_.userID_, response_.userRole_, response_.userLogin_, response_.userPassword_);
        }

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Add_Server")
    {
        if(!json_.contains("serverName") || !json_.contains("serverDescription") || !json_.contains("image"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::vector<uint8_t> receivedImage_ = imageWorker_.base64_decode(json_["image"].get<std::string>());
        std::string receivedServerName_ = json_["serverName"].get<std::string>();
        std::string receivedServerDescription_ = json_["serverDescription"].get<std::string>();

        AddResult response_ = serverManager_.addServer(connection_, receivedImage_, receivedServerName_, receivedServerDescription_);
        connectionPool_.returnConnection(connection_);

        response_.image_ = json_["image"].get<std::string>();

        std::string responseJsonForSender_;

        if(response_.code_ == "MY_SERVER_ADDED")
        {
            responseJsonForSender_ = jsonWorker_.createAddingServerSuccessJson(response_.code_, response_.serverID_, response_.image_, response_.serverName_, response_.serverDescription_);

            boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
                session_.lock()->do_write(responseJsonForSender_);
            });

            response_.code_ = "ADD_NEW_SERVER";

            std::string responseJsonForOther_ = jsonWorker_.createAddingServerSuccessJson(response_.code_, response_.serverID_, response_.image_, response_.serverName_, response_.serverDescription_);

            boost::asio::post(executor_, [this, session_, &connUsers_, responseJsonForOther_](){
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }

                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJsonForOther_);
                    }
                }
            });
        }
        else
        {
            responseJsonForSender_ = jsonWorker_.createAddingServerUnsuccessJson(response_.code_);

            boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
                session_.lock()->do_write(responseJsonForSender_);
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
        std::vector<int> usersId_ = userManager_.getUsersOnServers(connection_, receivedServerId_);
        ServerDeleteStruct serverDeleteStruct_ = serverManager_.deleteServer(connection_, receivedServerId_);
        std::string responseJson_ = jsonWorker_.createDeleteServerJson(serverDeleteStruct_);

        if(serverDeleteStruct_.code_ == "SERVER_DELETED")
        {
            boost::asio::post(executor_, [this, &connUsers_, responseJson_, usersId_](){
                for(const auto& i : usersId_)
                {
                    auto session_ = connUsers_.getUser(i).lock();
                    if(session_)
                    {
                        session_->do_write(responseJson_);
                    }
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
        std::string responseJsonForOther_ = jsonWorker_.createDeleteFromUnverUserJson(receivedUserId_);

        boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
            session_.lock()->do_write(responseJsonForSender_);
        });

        if(response_ == "APPROVED")
        {
            boost::asio::post(executor_, [this, session_, responseJsonForOther_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJsonForOther_);
                    }
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
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        continue;
                    }
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJsonForOther_);
                    }
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
        AddUserOnServerResult response_ = userManager_.addUserOnServer(connection_, receivedUserId_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJsonForSender_ = jsonWorker_.createUserAddedOnServerJson(response_.code_, receivedUserId_, receivedServerId_);
        std::string responseJsonForOther_ = jsonWorker_.createDeleteUserOnServerJson(receivedUserId_, receivedServerId_);

        boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
            session_.lock()->do_write(responseJsonForSender_);
        });

        if(response_.code_ == "USER_ADDED")
        {
            std::string responseJsonAddInChat_ = jsonWorker_.createAddInChatJson(receivedServerId_, response_.avatar_, receivedUserId_, response_.lastName_, response_.firstName_, response_.middleName_);
            std::string responseJsonForAddedUser_ = jsonWorker_.createForAddedUserJson(receivedServerId_, response_.serverImage_, response_.serverName_, response_.serverDescription_);

            std::weak_ptr<Session> user_ = connUsers_.getUser(receivedUserId_);

            boost::asio::post(executor_, [this, user_, session_, responseJsonForOther_, responseJsonForAddedUser_, responseJsonAddInChat_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(!(i.second.owner_before(session_)) && !(session_.owner_before(i.second)))
                    {
                        if(auto s_ = i.second.lock())
                        {
                            s_->do_write(responseJsonAddInChat_);
                        }
                        continue;
                    }
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJsonAddInChat_);
                        s_->do_write(responseJsonForOther_);
                    }
                }
                for(const auto& i : connUsers_.getAuthorizeUsers())
                {
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJsonAddInChat_);
                    }
                }
                if(auto s_ = user_.lock())
                {
                    s_->do_write(responseJsonForAddedUser_);
                }
            });
        }
    }
    else if(json_["Info"] == "Get_Chats")
    {
        if(!json_.contains("serverId") || !json_.contains("userId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::vector<PrivateChatStruct> response_ = chatManager_.getPrivateChats(connection_, receivedServerId_, receivedUserId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetChatsJson(receivedServerId_, response_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Create_Chat")
    {
        if(!json_.contains("serverId") || !json_.contains("userId") || !json_.contains("companionId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedServerId_ = json_["serverId"].get<int>();
        int receivedUserId_ = json_["userId"].get<int>();
        int receivedCompanionId_ = json_["companionId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        int response_ = chatManager_.createChat(connection_, receivedServerId_, receivedUserId_, receivedCompanionId_);
        connectionPool_.returnConnection(connection_);

        if(response_ > 0)
        {
            std::string responseJsonForSender_ = jsonWorker_.createChatCreateForSenderJson(receivedServerId_, receivedUserId_, receivedCompanionId_, response_);
            std::string responseJsonForCompanion_ = jsonWorker_.createChatCreateForCompanionJson(receivedServerId_, receivedCompanionId_, receivedUserId_, response_);

            boost::asio::post(executor_, [this, session_, responseJsonForSender_](){
                session_.lock()->do_write(responseJsonForSender_);
            });

            std::weak_ptr<Session> companionUser_ = connUsers_.getUser(receivedCompanionId_);

            boost::asio::post(executor_, [this, companionUser_, responseJsonForCompanion_](){
                    if(auto s_ = companionUser_.lock())
                    {
                        s_->do_write(responseJsonForCompanion_);
                    }
            });
        }
    }
    else if(json_["Info"] == "Get_Users_On_Server")
    {
        if(!json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::vector<UsersOnServerStruct> response_ = userManager_.getUsersOnServer(connection_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetUsersOnServerJson(receivedServerId_, response_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Add_Admin_On_Server")
    {
        if(!json_.contains("userId") || !json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.addAdminOnServer(connection_, receivedUserId_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createAddAdminOnServerJson(response_, receivedServerId_, receivedUserId_);

        std::weak_ptr<Session> user_ = connUsers_.getUser(receivedUserId_);

        if(response_ == "ADMIN_ADDED")
        {
            std::string responseJsonForUser_ = jsonWorker_.createAddAdminOnServerForUserJson(response_, receivedServerId_);

            boost::asio::post(executor_, [this, responseJsonForUser_, user_](){
                if(auto s_ = user_.lock())
                {
                    s_->do_write(responseJsonForUser_);
                }
            });
        }

        if(response_ != "ADMIN_ADDED")
        {
            boost::asio::post(executor_, [this, responseJson_, session_](){
                session_.lock()->do_write(responseJson_);
            });
        }
        else
        {   
            boost::asio::post(executor_, [this, responseJson_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJson_);
                    }
                }
            });
        }
    }
    else if(json_["Info"] == "Remove_Admin_On_Server")
    {
        if(!json_.contains("userId") || !json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.removeAdminOnServer(connection_, receivedUserId_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createRemoveAdminOnServerJson(response_, receivedServerId_, receivedUserId_);

        std::weak_ptr<Session> user_ = connUsers_.getUser(receivedUserId_);

        if(response_ == "ADMIN_REMOVED")
        {
            std::string responseJsonForUser_ = jsonWorker_.createRemoveAdminOnServerForUserJson(response_, receivedServerId_);

            boost::asio::post(executor_, [this, responseJsonForUser_, user_](){
                if(auto s_ = user_.lock())
                {
                    s_->do_write(responseJsonForUser_);
                }
            });
        }

        if(response_ != "ADMIN_REMOVED")
        {
            boost::asio::post(executor_, [this, responseJson_, session_](){
                session_.lock()->do_write(responseJson_);
            });
        }
        else
        {   
            boost::asio::post(executor_, [this, responseJson_, &connUsers_](){
                for(const auto& i : connUsers_.getAuthorizeAdmins())
                {
                    if(auto s_ = i.second.lock())
                    {
                        s_->do_write(responseJson_);
                    }
                }
            });
        }
    }
    else if(json_["Info"] == "Get_Server_Role")
    {
        if(!json_.contains("userId") || !json_.contains("serverId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::string response_ = userManager_.getServerRole(connection_, receivedUserId_, receivedServerId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetServerRoleJson(response_, receivedServerId_, receivedUserId_);
        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Get_Chat_Data")
    {
        if(!json_.contains("userId") || !json_.contains("serverId") || !json_.contains("chatId"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();
        int receivedChatId_ = json_["chatId"].get<int>();

        auto connection_ = connectionPool_.getConnection();
        std::vector<ChatHistoryResult> responseHistory_ = chatManager_.getChatHistory(connection_, receivedServerId_, receivedUserId_, receivedChatId_);
        ChatDataResult responseData_ = chatManager_.getChatData(connection_, receivedServerId_, receivedUserId_, receivedChatId_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createGetChatDataJson(responseHistory_, responseData_, receivedUserId_, receivedServerId_, receivedChatId_);

        boost::asio::post(executor_, [this, session_, responseJson_](){
            session_.lock()->do_write(responseJson_);
        });
    }
    else if(json_["Info"] == "Send_Message")
    {
        if(!json_.contains("userId") || !json_.contains("serverId") ||
           !json_.contains("chatId") || !json_.contains("message"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        int receivedUserId_ = json_["userId"].get<int>();
        int receivedServerId_ = json_["serverId"].get<int>();
        int receivedChatId_ = json_["chatId"].get<int>();
        std::string receivedMessage_ = json_["message"].get<std::string>();

        auto connection_ = connectionPool_.getConnection();
        SetMessageResult response_ = messageManager_.setNewMessage(connection_, receivedServerId_, receivedUserId_, receivedChatId_, receivedMessage_);
        connectionPool_.returnConnection(connection_);

        if(!response_.message_.empty())
        {
            std::string responseJsonForSender_ = jsonWorker_.createSetMessageForSenderJson(receivedUserId_, response_.messageId_, receivedServerId_, receivedChatId_, receivedMessage_, response_.time_);
            std::string responseJsonForCompanion_ = jsonWorker_.createSetMessageForCompanionJson(receivedUserId_, response_.messageId_, receivedServerId_, receivedChatId_, receivedMessage_, response_.time_);

            std::weak_ptr<Session> companion_ = connUsers_.getUser(response_.companionId_);

            boost::asio::post(executor_, [this, session_, responseJsonForSender_, responseJsonForCompanion_, &connUsers_, companion_](){
                session_.lock()->do_write(responseJsonForSender_);

                if(auto s_ = companion_.lock())
                {
                    s_->do_write(responseJsonForCompanion_);
                }
            });
        }
    }
}

