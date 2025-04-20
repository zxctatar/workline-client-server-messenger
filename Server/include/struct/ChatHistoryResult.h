#ifndef CHATHISTORYRESULT_H
#define CHATHISTORYRESULT_H

#include <string>
#include "nlohmann/json.hpp""

struct ChatHistoryResult
{
    int messageId_;
    std::string message_;
    std::string time_;
    bool isCompanion_;
    bool viewed_;

    std::string firstName_;
    std::string lastName_;
    std::string middleName_;
    std::string email_;
    std::string birthDate_;
    std::string phoneNumber_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"messageId", messageId_},
            {"message", message_},
            {"time", time_},
            {"isCompanion", isCompanion_},
            {"viewed", viewed_}
        };
    }
};

#endif // CHATHISTORYRESULT_H
