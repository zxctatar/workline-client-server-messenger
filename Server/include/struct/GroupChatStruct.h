#ifndef GROUPCHATSTRUCT_H
#define GROUPCHATSTRUCT_H

#include <string>
#include <nlohmann/json.hpp>

struct GroupChatStruct
{
    int chatId_;
    std::string chatName_;
    std::string avatar_;
    std::string lastMessage_;
    std::string messageTime_;
    int newMessagesCount_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"chatId", chatId_},
            {"chatName", chatName_},
            {"avatar", avatar_},
            {"lastMessage", lastMessage_},
            {"messageTime", messageTime_},
            {"newMessagesCount", newMessagesCount_}
        };
    }
};

#endif // GROUPCHATSTRUCT_H
