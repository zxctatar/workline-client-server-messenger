#ifndef CHATSDBMANAGER_H
#define CHATSDBMANAGER_H

#include <memory>
#include "struct/PrivateChatStruct.h"
#include "struct/ChatHistoryResult.h"
#include "DBConnection.h"
#include "ImageWorker.h"
#include "struct/ChatDataResult.h"
#include "struct/CreateGroupChatResult.h"
#include "struct/GroupChatStruct.h"
#include "struct/GroupChatDataStruct.h"

class ChatsDBManager
{
public:
    explicit ChatsDBManager();
    ~ChatsDBManager();

    std::vector<PrivateChatStruct> getPrivateChats(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_);
    int createChat(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int companionId_);
    std::vector<ChatHistoryResult> getChatHistory(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_, const bool isGroup_);
    ChatDataResult getChatData(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_);
    CreateGroupChatResult createGroupChat(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const std::string& groupName_, const std::vector<uint8_t>& groupAvatar_, const std::vector<int>& addedUsers_);
    std::vector<GroupChatStruct> getGroupChats(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_);
    GroupChatDataResult getGroupChatData(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_);

private:
    ImageWorker imageWorker_;
};

#endif // CHATSDBMANAGER_H
