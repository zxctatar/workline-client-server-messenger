#ifndef UNVERUSERSTRUCT_H
#define UNVERUSERSTRUCT_H

#include <string>
#include <nlohmann/json.hpp>

struct UnverUserStruct
{
    int userId_;
    std::string avatar_;
    std::string firstName_;
    std::string lastName_;
    std::string middleName_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"avatar", avatar_},
            {"userId", userId_},
            {"firstName", firstName_},
            {"lastName", lastName_},
            {"middleName", middleName_}
        };
    }
};

#endif // UNVERUSERSTRUCT_H
