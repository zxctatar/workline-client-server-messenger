#ifndef CHATSDBMANAGER_H
#define CHATSDBMANAGER_H

#include <memory>
#include "struct/PrivateChatStruct.h"
#include "struct/ChatHistoryResult.h"
#include "DBConnection.h"

class ChatsDBManager
{
public:
    explicit ChatsDBManager();
    ~ChatsDBManager();

    std::vector<PrivateChatStruct> getPrivateChats(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_);
    int createChat(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int companionId_);
    std::vector<ChatHistoryResult> getChatHistory(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_);

private:

};

#endif // CHATSDBMANAGER_H
