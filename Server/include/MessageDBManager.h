#ifndef MESSAGEDBMANAGER_H
#define MESSAGEDBMANAGER_H

#include <string>
#include <memory>
#include "DBConnection.h"
#include "struct/SetMessageResult.h"

class MessageDBManager
{
public:
    explicit MessageDBManager();
    ~MessageDBManager();

    SetMessageResult setNewMessage(std::shared_ptr<DBConnection> connection_, const int userId_, const int chatId_, const std::string& message_, const bool isGroup_);
    int markMessage(std::shared_ptr<DBConnection> connection_, const int userId_, const int chatId_, const int messageId_, const bool isGroup_);

private:
};

#endif // MESSAGEDBMANAGER_H
