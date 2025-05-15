#ifndef CHATHISTORYCONTROLLER_H
#define CHATHISTORYCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "ChatHistoryModel.h"
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
#include "SelectedChatManager.h"
#include "JsonWorker.h"
#include "Encryption.h"

class ChatHistoryController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatHistoryController(QObject* parent = nullptr);
    ~ChatHistoryController();

    Q_INVOKABLE void sendMessage(const int chatId_, const bool isGroup_, const QString& message_);
    Q_INVOKABLE void getChatData(const int chatId_, const bool isGroup_);
    Q_INVOKABLE ChatHistoryModel* getModel();
    Q_INVOKABLE void markMessageAsRead(const int messageId_);

signals:
    void setChatIdAndGroupSignal(const int chatId_, const bool isGroup_);
    void getChatDataSignal(const QString& info_);
    void sendMessageSignal(const QString& info_);
    void scrollDownSignal();
    void clearChatIdSignal();
    void markMessageSignal(const QString& info_);

public slots:
    void slotSetChatId(const int chatId_);
    void slotSetChatData(const QJsonObject& jsonObj_);
    void slotSetNewMessage(const QJsonObject& jsonObj_);
    void slotServerChanged(const int serverId_);
    void slotMarkMessageProcessing(const QJsonObject& jsonObj_);

private:
    JsonWorker jsonWorker_;
    Encryption encryption_;
    ChatHistoryModel* historyModel_;
};

#endif // CHATHISTORYCONTROLLER_H
