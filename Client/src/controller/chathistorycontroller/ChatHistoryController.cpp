#include "../../../include/ChatHistoryController.h"

ChatHistoryController::ChatHistoryController(QObject* parent)
    : QObject(parent)
    , historyModel_(new ChatHistoryModel(this))
{
}

ChatHistoryController::~ChatHistoryController()
{
}

ChatHistoryModel* ChatHistoryController::getModel()
{
    return historyModel_;
}

void ChatHistoryController::sendMessage(const int chatId_, const bool isGroup_, const QString& message_)
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString encryptMessage_ = encryption_.encrypt(message_);

    QString request_ = jsonWorker_.createJsonSendMessage(chatId_, isGroup_, userId_, serverId_, encryptMessage_);

    emit sendMessageSignal(request_);
}

void ChatHistoryController::slotSetChatId(const int chatId_)
{
    historyModel_->clearMessages();
    bool isGroup_ = SelectedChatManager::instance().getGroup();

    emit setChatIdAndGroupSignal(chatId_, isGroup_);
}

void ChatHistoryController::getChatData(const int chatId_, const bool isGroup_)
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetChatHistory(chatId_, serverId_, userId_, isGroup_);
    emit getChatDataSignal(request_);
}

void ChatHistoryController::slotSetChatData(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();

    bool isGroup_ = SelectedChatManager::instance().getGroup();

    if(isGroup_)
    {
        QString receivedGroupName_ = jsonObj_["groupName"].toString();
        int receivedUsersCount_ = jsonObj_["usersCount"].toInt();

        SelectedChatManager::instance().setGroupChatData(receivedGroupName_, receivedUsersCount_);
    }
    else
    {
        QString receivedFirstName_ = jsonObj_["firstName"].toString();
        QString receivedLastName_ = jsonObj_["lastName"].toString();
        QString receivedMiddleName_ = jsonObj_["middleName"].toString();
        QString receivedEmail_ = jsonObj_["email"].toString();
        QString receivedBirthDate_ = jsonObj_["birthDate"].toString();
        QString receivedPhoneNumber_ = jsonObj_["phoneNumber"].toString();

        SelectedChatManager::instance().setChatData(receivedFirstName_, receivedLastName_, receivedMiddleName_, receivedBirthDate_, receivedEmail_, receivedPhoneNumber_);
    }

    if(serverId_ == SelectedServerManager::instance().getServerId() && chatId_ == SelectedChatManager::instance().getChatId())
    {
        QJsonArray array_ = jsonObj_["messages"].toArray();

        for(const QJsonValue& val_ : array_)
        {
            if(!val_.isObject())
            {
                continue;
            }

            QJsonObject mObj_ = val_.toObject();

            int senderId_ = mObj_["senderId"].toInt();
            int messageId_ = mObj_["messageId"].toInt();
            QString message_ = encryption_.decrypt(mObj_["message"].toString());
            QString stringTime_ = mObj_["time"].toString();

            QString trimmed_ = stringTime_.left(19);
            QDateTime dateTime_ = QDateTime::fromString(trimmed_, "yyyy-MM-dd HH:mm:ss");
            QTime time_ = dateTime_.time();
            stringTime_ = time_.toString("HH:mm");

            bool isCompanion_ = mObj_["isCompanion"].toBool();
            bool viewed_ = mObj_["viewed"].toBool();

            historyModel_->addMessage(senderId_, serverId_, chatId_, messageId_, message_, stringTime_, isCompanion_, viewed_);
        }
    }
}

void ChatHistoryController::slotSetNewMessage(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();
    int senderId_ = jsonObj_["senderId"].toInt();
    bool isGroup_ = jsonObj_["isGroup"].toBool();

    if(serverId_ == SelectedServerManager::instance().getServerId() && chatId_ == SelectedChatManager::instance().getChatId() && isGroup_ == SelectedChatManager::instance().getGroup())
    {
        int messageId_ = jsonObj_["messageId"].toInt();
        QString message_ = encryption_.decrypt(jsonObj_["message"].toString());
        QString stringTime_ = jsonObj_["time"].toString();

        QString trimmed_ = stringTime_.left(19);
        QDateTime dateTime_ = QDateTime::fromString(trimmed_, "yyyy-MM-dd HH:mm:ss");
        QTime time_ = dateTime_.time();
        stringTime_ = time_.toString("HH:mm");

        bool isCompanion_ = jsonObj_["isCompanion"].toBool();
        bool viewed_ = jsonObj_["viewed"].toBool();

        historyModel_->addMessage(senderId_, serverId_, chatId_, messageId_, message_, stringTime_, isCompanion_, viewed_);
    }
    if(!jsonObj_["isCompanion"].toBool())
    {
        emit scrollDownSignal();
    }
}

void ChatHistoryController::slotServerChanged(const int serverId_)
{
    Q_UNUSED(serverId_);

    emit clearChatIdSignal();
}

void ChatHistoryController::markMessageAsRead(const int messageId_)
{
    int chatId_ = SelectedChatManager::instance().getChatId();
    int userId_ = UserAccountManager::instance().getUserId();
    bool isGroup_ = SelectedChatManager::instance().getGroup();

    QString request_ = jsonWorker_.createJsonMarkMessageAsRead(messageId_, userId_, chatId_, isGroup_);

    emit markMessageSignal(request_);
}

void ChatHistoryController::slotMarkMessageProcessing(const QJsonObject& jsonObj_)
{
    int messageId_ = jsonObj_["messageId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();
    bool viewed_ = jsonObj_["viewed"].toBool();

    if(SelectedChatManager::instance().getChatId() == chatId_)
    {
        historyModel_->markMessage(messageId_, viewed_);
    }
}
