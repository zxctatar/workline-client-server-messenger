#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include <string>

struct LoginResult {
    std::string code_;
    int userID_;
    std::string userRole_;
};

#endif // LOGINRESULT_H
