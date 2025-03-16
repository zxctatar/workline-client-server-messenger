#ifndef RECONNECTRESULT_H
#define RECONNECTRESULT_H

#include <string>

struct ReconnectResult {
    std::string code_;
    int userID_;
    std::string userRole_;
};

#endif // RECONNECTRESULT_H
