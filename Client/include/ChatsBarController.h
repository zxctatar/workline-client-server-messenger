#ifndef CHATSBARCONTROLLER_H
#define CHATSBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
#include "SelectedChatManager.h"
#include "ChatModel.h"
#include "ImageWorker.h"

class ChatsBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatsBarController(QObject* parent = nullptr);
    ~ChatsBarController();

    Q_INVOKABLE ChatModel* getChatModel();
    Q_INVOKABLE void createChat(const int companionId_) const;
    Q_INVOKABLE void sendChatId(const int chatId_) const;

signals:
    void getChatsSignal(const QString& info_);
    void createChatSignal(const QString& info_) const;
    void serverChangedSignal();
    void sendChatIdSignal(const int chatId_) const;

public slots:
    void slotGetChats(const int serverId_);
    void slotChatsProcessing(const QJsonObject& jsonObj_);
    void slotChatCreatedProcessing(const QJsonObject& jsonObj_);
    void slotAddUserInChatProcessing(const QJsonObject& jsonObj_);
    void slotClearChat();
    void slotSetNewLastMessage(const QJsonObject& jsonObj_);

private:
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
    ChatModel* chatModel_;
};

#endif // CHATSBARCONTROLLER_H
