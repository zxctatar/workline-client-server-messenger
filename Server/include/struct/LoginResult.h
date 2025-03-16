#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include <string>

struct LoginResult {
    std::string code_;
    int userID_;
    std::string userRole_;
    std::string userLogin_;
    std::string userPassword_;
    std::string userFirstName_;
    std::string userLastName_;
    std::string userMiddleName_;
    std::string userEmail_;
    std::string userPhoneNumber;
};

#endif // LOGINRESULT_H
