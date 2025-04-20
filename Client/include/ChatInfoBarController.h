#ifndef CHATINFOBARCONTROLLER_H
#define CHATINFOBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"
#include "SelectedChatManager.h"

class ChatInfoBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatInfoBarController(QObject* parent = nullptr);
    ~ChatInfoBarController();

    Q_INVOKABLE void getChatId();

signals:
    void getChatDataSignal(const QString& info_);

    void setChatDataSignal(const QString& firstName_, const QString& lastName_, const QString& middleName_, const QString& email, const QString& phoneNumber_, const QString& birthDate_, const bool isGroupChat_);
    void setChatAvatarSignal(const QString& avatarPath_);
    void clearChatDataSignal();
    void setChatIdSignal(const int chatId_);
    void clearChatIdSignal();

public slots:
    void slotSetChatData();
    void slotSetChatAvatar();
    void slotClearChatData();
    void slotServerChanged(const int serverId_);
    void slotChatIdChanged(const int chatId_);

private:
    JsonWorker jsonWorker_;
};

#endif // CHATINFOBARCONTROLLER_H
