#include "../../../include/ChatsBarController.h"

ChatsBarController::ChatsBarController(QObject* parent)
    : QObject(parent)
    , chatModel_(new ChatModel(this))
{
}

ChatsBarController::~ChatsBarController()
{
}

void ChatsBarController::slotGetChats(const int serverId_)
{
    if(chatModel_->getSize() > 0)
    {
        chatModel_->deleteChats();
        emit serverChangedSignal();
    }

    int userId_ = UserAccountManager::instance().getUserId();
    QString request_ = jsonWorker_.createJsonGetChats(serverId_, userId_);
    emit getChatsSignal(request_);
}

void ChatsBarController::slotChatsProcessing(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();

    if(serverId_ == SelectedServerManager::instance().getServerId())
    {
        QJsonArray chatArray_ = jsonObj_["PrivateChats"].toArray();

        for(const QJsonValue& val : chatArray_)
        {
            if(!val.isObject())
            {
                continue;
            }

            QJsonObject chat_ = val.toObject();

            int compaonionId_ = chat_["compaonionId"].toInt();
            int chatId_ = chat_["chatId"].toInt();
            QString firstName_ = chat_["firstName"].toString();
            QString lastName_ = chat_["lastName"].toString();
            QString middleName_ = chat_["middleName"].toString();
            QString lastMessage_ = chat_["lastMessage"].toString();
            QString messageTime_ = chat_["messageTime"].toString();
            bool isChat_ = chat_["isChat"].toBool();

            chatModel_->addChat(compaonionId_, chatId_, firstName_, lastName_, middleName_, lastMessage_, messageTime_, isChat_);
        }
    }
}

ChatModel* ChatsBarController::getChatModel()
{
    return chatModel_;
}

void ChatsBarController::createChat(const int companionId_) const
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonCreateChat(serverId_, userId_, companionId_);

    emit createChatSignal(request_);
}

void ChatsBarController::slotChatCreatedProcessing(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();

    if(serverId_ == SelectedServerManager::instance().getServerId())
    {
        int companionId_ = jsonObj_["companionId"].toInt();

        chatModel_->chatCreated(serverId_, companionId_, chatId_);
    }
}

void ChatsBarController::slotAddUserInChatProcessing(const int userId_, const int serverId_, const QString& lastName_, const QString& firstName_, const QString& middleName_)
{
    if(serverId_ == SelectedServerManager::instance().getServerId())
    {
        chatModel_->addChat(userId_, 0, firstName_, lastName_, middleName_, "", "", false);
    }
}

void ChatsBarController::slotClearChat()
{
    chatModel_->clearChat();
}

void ChatsBarController::sendChatId(const int chatId_) const
{
    SelectedChatManager::instance().setChatId(chatId_);
}
