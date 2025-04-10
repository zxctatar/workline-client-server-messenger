#include "../../include/JsonWorker.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

JsonWorker::JsonWorker()
{}

JsonWorker::~JsonWorker()
{}

nlohmann::json JsonWorker::parceJson(const std::string& data_) const
{
    try
    {
        nlohmann::json request_ = nlohmann::json::parse(data_);
        return request_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createUserIdJson(const int id_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "UserID";
        json_["ID"] = id_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createRegistrationCodeJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Registration";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createLoginSuccessJson(const std::string& code_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& email_, const std::string& phoneNumber_, const int userID_, const std::string& userRole_, const std::string& userLogin_, const std::string& userPassword_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Login";
        json_["Code"] = code_;
        json_["UserFirstName"] = firstName_;
        json_["UserLastName"] = lastName_;
        json_["UserMiddleName"] = middleName_;
        json_["UserEmail"] = email_;
        json_["UserPhoneNumber"] = phoneNumber_;
        json_["UserId"] = userID_;
        json_["UserRole"] = userRole_;
        json_["UserLogin"] = userLogin_;
        json_["UserPassword"] = userPassword_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createLoginUnsuccessJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Login";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createAddingServerSuccessJson(const std::string& code_, const int serverID_, const std::string& serverName_, const std::string& serverDescription_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_Server";
        json_["Code"] = code_;
        json_["ServerID"] = serverID_;
        json_["ServerName"] = serverName_;
        json_["ServerDescription"] = serverDescription_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}
std::string JsonWorker::createAddingServerUnsuccessJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_Server";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetServersJson(const std::vector<ServerStruct>& servers_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Servers";

        for(const auto& i : servers_)
        {
            nlohmann::json jsonServer_;
            i.to_json(jsonServer_);
            json_["Servers"].push_back(jsonServer_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createDeleteServerJson(const ServerDeleteStruct& serverDeleteStruct_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "DeleteServer";
        json_["serverId"] = serverDeleteStruct_.serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetUnverUsersJson(const std::vector<UnverUserStruct>& unverUsers_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_UnverUsers";

        for(const auto& i : unverUsers_)
        {
            nlohmann::json jsonUnverUser_;
            i.to_json(jsonUnverUser_);
            json_["UnverUsers"].push_back(jsonUnverUser_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createApproveUserJson(const std::string& response_, const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Approve_User";
        json_["code"] = response_;
        json_["userId"] = userId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createRejectUserJson(const std::string& response_, const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Reject_User";
        json_["code"] = response_;
        json_["userId"] = userId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createDeleteFromUnverUserJson(const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Delete_unver_user";
        json_["userId"] = userId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createCandidateUsersJson(const std::vector<CandidateUserStruct>& candidateUsers_, const int serverId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Candidate_Users";
        json_["serverId"] = serverId_;

        for(const auto& i : candidateUsers_)
        {
            nlohmann::json jsonCandidateUser_;
            i.to_json(jsonCandidateUser_);
            json_["CandidateUser"].push_back(jsonCandidateUser_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createUserAddedOnServerJson(const std::string& response_, const int userId_, const int serverId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_User_On_Server";
        json_["code"] = response_;
        json_["userId"] = userId_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createDeleteUserOnServerJson(const int userId_, const int serverId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Delete_User_On_Server";
        json_["userId"] = userId_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetChatsJson(const int serverId_, std::vector<PrivateChatStruct>& chats_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Chats";
        json_["serverId"] = serverId_;

        for(const auto& i : chats_)
        {
            nlohmann::json jsonChat_;
            i.to_json(jsonChat_);
            json_["PrivateChats"].push_back(jsonChat_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createChatCreateForSenderJson(const int serverId_, const int userId_, const int companionId_, const int chatId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Create_Chat";
        json_["userId"] = userId_;
        json_["companionId"] = companionId_;
        json_["serverId"] = serverId_;
        json_["chatId"] = chatId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createChatCreateForCompanionJson(const int serverId_, const int userId_, const int companionId_, const int chatId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Create_Chat";
        json_["userId"] = userId_;
        json_["companionId"] = companionId_;
        json_["serverId"] = serverId_;
        json_["chatId"] = chatId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetUsersOnServerJson(const int serverId_, const std::vector<UsersOnServerStruct>& users_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Users_On_Server";
        json_["serverId"] = serverId_;

        for(const auto& i : users_)
        {
            nlohmann::json user_;
            i.to_json(user_);
            json_["users"].push_back(user_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createAddInChatJson(const int serverId_, const int userId_, const std::string lastName_, const std::string firstName_, const std::string middleName_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_User_In_Chat";
        json_["serverId"] = serverId_;
        json_["userId"] = userId_;
        json_["lastName"] = lastName_;
        json_["firstName"] = firstName_;
        json_["middleName"] = middleName_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createForAddedUserJson(const int serverId_, std::string serverName_, std::string serverDescription_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_New_Server";
        json_["serverId"] = serverId_;
        json_["serverName"] = serverName_;
        json_["serverDescription"] = serverDescription_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createAddAdminOnServerJson(std::string& code_ ,const int serverId_, const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_Admin_On_Server";
        json_["code"] = code_;
        json_["userId"] = userId_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createRemoveAdminOnServerJson(std::string& code_, const int serverId_, const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Remove_Admin_On_Server";
        json_["code"] = code_;
        json_["userId"] = userId_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createAddAdminOnServerForUserJson(std::string& code_, const int serverId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Server_Role_Add";
        json_["code"] = code_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createRemoveAdminOnServerForUserJson(std::string& code_, const int serverId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Server_Role_Removed";
        json_["code"] = code_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetServerRoleJson(std::string& code_, const int serverId_, const int userId_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Server_Role";
        json_["code"] = code_;
        json_["userId"] = userId_;
        json_["serverId"] = serverId_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}
