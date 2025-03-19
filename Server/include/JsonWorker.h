#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <nlohmann/json.hpp>
#include "struct/ServerStruct.h"
#include "struct/ServerDeleteStruct.h"
#include "struct/UnverUserStruct.h"

class JsonWorker
{
public:
    explicit JsonWorker();

    nlohmann::json parceJson(const std::string& data_) const;

    std::string createUserIdJson(const int id_);
    std::string createRegistrationCodeJson(const std::string& code_);
    std::string createLoginSuccessJson( const std::string& code_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& email_, const std::string& phoneNumber_, const int userID_, const std::string& userRole_, const std::string& userLogin_, const std::string& userPassword_);
    std::string createLoginUnsuccessJson(const std::string& code_);
    std::string createAddingServerSuccessJson(const std::string& code_, const int serverID_, const std::string& serverName_, const std::string& serverDescription);
    std::string createAddingServerUnsuccessJson(const std::string& code_);
    std::string createGetServersJson(const std::vector<ServerStruct>& servers_);
    std::string createDeleteServerJson(const ServerDeleteStruct& serverDeleteStruct_);
    std::string createGetUnverUsersJson(const std::vector<UnverUserStruct>& unverUsers_);
    std::string createApproveUserJson(const std::string& response_, const int userId_);
    std::string createRejectUserJson(const std::string& response_, const int userId_);
    std::string createDeleteFromUnverUserJson(const int userId_);

    ~JsonWorker();

private:

};

#endif // JSONWORKER_H
