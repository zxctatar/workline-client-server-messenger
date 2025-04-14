#include "../../../include/ChatHistoryController.h"

ChatHistoryController::ChatHistoryController(QObject* parent)
    : QObject(parent)
{
}

ChatHistoryController::~ChatHistoryController()
{
}

void ChatHistoryController::sendMessage(const int chatId_, const QString& message_)
{

}

void ChatHistoryController::slotSetChatId(const int chatId_)
{
    emit setChatIdSignal(chatId_);
}

void ChatHistoryController::getChatHistory(const int chatId_)
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetChatHistory(chatId_, serverId_, userId_);
    emit getChatHistorySignal(request_);
}
