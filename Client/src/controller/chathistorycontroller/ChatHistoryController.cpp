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

void ChatHistoryController::sendMessage(const int chatId_, const QString& message_)
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonSendMessage(chatId_, userId_, serverId_, message_);

    emit sendMessageSignal(request_);
}

void ChatHistoryController::slotSetChatId(const int chatId_)
{
    historyModel_->clearMessages();
    emit setChatIdSignal(chatId_);
}

void ChatHistoryController::getChatData(const int chatId_)
{
    int userId_ = UserAccountManager::instance().getUserId();
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetChatHistory(chatId_, serverId_, userId_);
    emit getChatDataSignal(request_);
}

void ChatHistoryController::slotSetChatData(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();

    QString receivedFirstName_ = jsonObj_["firstName"].toString();
    QString receivedLastName_ = jsonObj_["lastName"].toString();
    QString receivedMiddleName_ = jsonObj_["middleName"].toString();
    QString receivedEmail_ = jsonObj_["email"].toString();
    QString receivedBirthDate_ = jsonObj_["birthDate"].toString();
    QString receivedPhoneNumber_ = jsonObj_["phoneNumber"].toString();

    SelectedChatManager::instance().setChatData(receivedFirstName_, receivedLastName_, receivedMiddleName_, receivedBirthDate_, receivedEmail_, receivedPhoneNumber_);

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
            QString message_ = mObj_["message"].toString();
            QString time_ = mObj_["time"].toString();
            bool isCompanion_ = mObj_["isCompanion"].toBool();
            bool viewed_ = mObj_["viewed"].toBool();

            historyModel_->addMessage(senderId_, serverId_, chatId_, messageId_, message_, time_, isCompanion_, viewed_);
        }
    }
}

void ChatHistoryController::slotSetNewMessage(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();
    int chatId_ = jsonObj_["chatId"].toInt();
    int senderId_ = jsonObj_["senderId"].toInt();

    qDebug() << senderId_;

    if(serverId_ == SelectedServerManager::instance().getServerId() && chatId_ == SelectedChatManager::instance().getChatId())
    {
        int messageId_ = jsonObj_["messageId"].toInt();
        QString message_ = jsonObj_["message"].toString();
        QString time_ = jsonObj_["time"].toString();
        bool isCompanion_ = jsonObj_["isCompanion"].toBool();
        bool viewed_ = jsonObj_["viewed"].toBool();

        historyModel_->addMessage(senderId_, serverId_, chatId_, messageId_, message_, time_, isCompanion_, viewed_);
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
