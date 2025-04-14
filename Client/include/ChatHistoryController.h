#ifndef CHATHISTORYCONTROLLER_H
#define CHATHISTORYCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
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

signals:
    void setChatIdSignal(const int chatId_);
    void getChatHistorySignal(const QString info_);

public slots:
    void slotSetChatId(const int chatId_);

private:
    JsonWorker jsonWorker_;
};

#endif // CHATHISTORYCONTROLLER_H
