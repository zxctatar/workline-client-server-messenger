#ifndef CHATHISTORYCONTROLLER_H
#define CHATHISTORYCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "ChatHistoryModel.h"
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
#include "SelectedChatManager.h"
#include "JsonWorker.h"

class ChatHistoryController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatHistoryController(QObject* parent = nullptr);
    ~ChatHistoryController();

    Q_INVOKABLE void sendMessage(const int chatId_, const QString& message_);
    Q_INVOKABLE void getChatHistory(const int chatId_);
    Q_INVOKABLE ChatHistoryModel* getModel();

signals:
    void setChatIdSignal(const int chatId_);
    void getChatHistorySignal(const QString& info_);
    void sendMessageSignal(const QString& info_);
    void scrollDown();

public slots:
    void slotSetChatId(const int chatId_);
    void slotSetChatHistory(const QJsonObject& jsonObj_);
    void slotSetNewMessage(const QJsonObject& jsonObj_);

private:
    JsonWorker jsonWorker_;
    ChatHistoryModel* historyModel_;
};

#endif // CHATHISTORYCONTROLLER_H
