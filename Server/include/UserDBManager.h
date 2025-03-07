#ifndef USERDBMANAGER_H
#define USERDBMANAGER_H

#include "DBConnection.h"
#include "struct/LoginResult.h"
#include <string>
#include <memory>

class UserDBManager
{
public:
    explicit UserDBManager();
    ~UserDBManager();

    std::string regUser(std::shared_ptr<DBConnection> connection_, const std::string& lastName_, const std::string& firstName_, const std::string& middleName_, const std::string& login_, const long long int phoneNumber_, const std::string& email_, const std::string& password_) const;
    LoginResult loginUser(std::shared_ptr<DBConnection> connection_, const std::string& login_, const std::string& password_) const;

private:
};

#endif // USERDBMANAGER_H
