#ifndef ADDRESULT_H
#define ADDRESULT_H

#include <string>

struct AddResult {
    std::string code_;
    int serverID_;
    std::string image_;
    std::string serverName_;
    std::string serverDescription_;
};

#endif // ADDRESULT_H
