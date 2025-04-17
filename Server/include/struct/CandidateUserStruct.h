#ifndef CANDIDATEUSERSTRUCT_H
#define CANDIDATEUSERSTRUCT_H

#include <string>
#include <nlohmann/json.hpp>

struct CandidateUserStruct
{
    int userId_;
    std::string avatar_;
    std::string firstName_;
    std::string lastName_;
    std::string middleName_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"userId", userId_},
            {"avatar", avatar_},
            {"firstName", firstName_},
            {"lastName", lastName_},
            {"middleName", middleName_}
        };
    }
};

#endif // CANDIDATEUSERSTRUCT_H
