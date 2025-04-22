#ifndef PRIVATECHATSTRUCT_H
#define PRIVATECHATSTRUCT_H

#include <string>
#include <nlohmann/json.hpp>

struct PrivateChatStruct
{
    int companionId_;
    int chatId_;
    std::string avatar_;
    std::string firstName_;
    std::string lastName_;
    std::string middleName_;
    std::string lastMessage_;
    std::string messageTime_;
    bool isChat_;
    int newMessagesCount_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"compaonionId", companionId_},
            {"chatId", chatId_},
            {"avatar", avatar_},
            {"firstName", firstName_},
            {"lastName", lastName_},
            {"middleName", middleName_},
            {"lastMessage", lastMessage_},
            {"messageTime", messageTime_},
            {"isChat", isChat_},
            {"newMessagesCount", newMessagesCount_}
        };
    }
};

#endif // PRIVATECHATSTRUCT_H
