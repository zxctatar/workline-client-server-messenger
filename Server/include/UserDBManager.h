#ifndef USERDBMANAGER_H
#define USERDBMANAGER_H

#include "DBConnection.h"
#include "struct/LoginResult.h"
#include "struct/ReconnectResult.h"
#include "struct/UnverUserStruct.h"
#include "struct/CandidateUserStruct.h"
#include "struct/UsersOnServerStruct.h"
#include "struct/AddUserOnServerResult.h"
#include "ImageWorker.h"
#include <string>
#include <memory>

class UserDBManager
{
public:
    explicit UserDBManager();
    ~UserDBManager();

    std::string regUser(std::shared_ptr<DBConnection> connection_, const std::vector<uint8_t>& image_, const std::string& lastName_, const std::string& firstName_, const std::string& middleName_, const std::string& birthDate_, const std::string& login_, const long long int phoneNumber_, const std::string& email_, const std::string& password_) const;
    LoginResult loginUser(std::shared_ptr<DBConnection> connection_, const std::string& login_, const std::string& password_) const;
    ReconnectResult reconnectUser(std::shared_ptr<DBConnection> connection_, const std::string& login_, const std::string& password_) const;
    std::vector<int> getUsersOnServers(std::shared_ptr<DBConnection> connection_, const int serverId_) const;
    std::vector<UnverUserStruct> getUnverUsers(std::shared_ptr<DBConnection> connection_) const;
    std::string approveUser(std::shared_ptr<DBConnection> connection_, const int userId_) const;
    std::string rejectUser(std::shared_ptr<DBConnection> connection_, const int userId_) const;
    std::vector<CandidateUserStruct> getCandidateUsers(std::shared_ptr<DBConnection> connection_, const int serverId_) const;
    AddUserOnServerResult addUserOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_);
    std::vector<UsersOnServerStruct> getUsersOnServer(std::shared_ptr<DBConnection> connection_, const int serverId_) const;
    std::string addAdminOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const;
    std::string removeAdminOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const;
    std::string getServerRole(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const;

private:
    ImageWorker imageWorker_;
};

#endif // USERDBMANAGER_H
