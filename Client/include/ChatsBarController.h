#ifndef CHATSBARCONTROLLER_H
#define CHATSBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
#include "ChatModel.h"

class ChatsBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatsBarController(QObject* parent = nullptr);
    ~ChatsBarController();

    Q_INVOKABLE ChatModel* getChatModel();
    Q_INVOKABLE void createChat(const int companionId_) const;

signals:
    void getChatsSignal(const QString& info_);
    void createChatSignal(const QString& info_) const;
    void serverChangedSignal();

public slots:
    void slotGetChats(const int serverId_);
    void slotChatsProcessing(const QJsonObject& jsonObj_);
    void slotChatCreatedProcessing(const QJsonObject& jsonObj_);
    void slotAddUserInChatProcessing(const int userId_, const int serverId_, const QString& lastName_, const QString& firstName_, const QString& middleName_);
    void slotClearChat();

private:
    JsonWorker jsonWorker_;
    ChatModel* chatModel_;
};

#endif // CHATSBARCONTROLLER_H
