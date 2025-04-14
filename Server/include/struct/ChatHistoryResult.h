#ifndef CHATHISTORYRESULT_H
#define CHATHISTORYRESULT_H

#include <string>
#include "nlohmann/json.hpp""

struct ChatHistoryResult
{
    std::string message_;
    std::string time_;
    bool isCandidate_;
    bool viewed_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"message", message_},
            {"time", time_},
            {"isCandidate", isCandidate_},
            {"viewed", viewed_}
        };
    }
};

#endif // CHATHISTORYRESULT_H
