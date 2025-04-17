#ifndef USERSONSERVERSTRUCT_H
#define USERSONSERVERSTRUCT_H

#include <string>
#include <nlohmann/json.hpp>

struct UsersOnServerStruct
{
    int userId_;
    std::string avatar_;
    std::string firstName_;
    std::string lastName_;
    std::string middleName_;
    bool isServerAdmin_;
    bool isGlobalAdmin_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"userId", userId_},
            {"avatar", avatar_},
            {"firstName", firstName_},
            {"lastName", lastName_},
            {"middleName", middleName_},
            {"isServerAdmin", isServerAdmin_},
            {"isGlobalAdmin", isGlobalAdmin_}
        };
    }
};

#endif // USERSONSERVERSTRUCT_H
