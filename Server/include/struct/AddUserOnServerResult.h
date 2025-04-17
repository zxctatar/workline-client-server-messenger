#ifndef ADDUSERONSERVERRESULT_H
#define ADDUSERONSERVERRESULT_H

#include <string>
#include <nlohmann/json.hpp>

struct AddUserOnServerResult
{
    std::string code_;
    std::string avatar_;
    std::string lastName_;
    std::string firstName_;
    std::string middleName_;
    std::string serverImage_;
    std::string serverName_;
    std::string serverDescription_;
};

#endif // ADDUSERONSERVERRESULT_H
