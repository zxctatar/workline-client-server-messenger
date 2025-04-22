#ifndef CHATHISTORYRESULT_H
#define CHATHISTORYRESULT_H

#include <string>
#include "nlohmann/json.hpp"

struct ChatHistoryResult
{
    int senderId_;
    int messageId_;
    std::string message_;
    std::string time_;
    bool isCompanion_;
    bool viewed_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"senderId", senderId_},
            {"messageId", messageId_},
            {"message", message_},
            {"time", time_},
            {"isCompanion", isCompanion_},
            {"viewed", viewed_}
        };
    }
};

#endif // CHATHISTORYRESULT_H
