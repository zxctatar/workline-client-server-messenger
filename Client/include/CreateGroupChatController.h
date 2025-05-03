#ifndef CREATEGROUPCHATCONTROLLER_H
#define CREATEGROUPCHATCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <JsonWorker.h>
#include "SelectedServerManager.h"
#include "UserAccountManager.h"
#include "UsersModel.h"
#include "ImageWorker.h"

class CreateGroupChatController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CreateGroupChatController(QObject* parent = nullptr);
    ~CreateGroupChatController();

    Q_INVOKABLE void getUsers();
    Q_INVOKABLE UsersModel* getUsersModel();
    Q_INVOKABLE void saveAvatarAndName(const QString& q_groupAvatar, const QString& q_groupName);
    Q_INVOKABLE void addUser(const int userId_);
    Q_INVOKABLE void removeUser(const int userId_);
    Q_INVOKABLE void createChat();

public slots:
    void slotSetUsersOnServerPreparing(const QJsonObject& jsonObj_);
    void slotCodeProcessing(const QString& code_);

signals:
    void getUsersOnServerSignal(const QString& info_);
    void createGroupChatSignal(const QString& info_);

    void noUsersSignal();

    void codeErrorSignal();
    void codeGroupNameExistsSignal();
    void codeAccessDeniedSignal();
    void codeGroupCreatedSignal();
\
private:
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
    UsersModel* usersModel_;

    QString receivedGroupName_;
    QString receivedGroupAvatar_;
    QVector<int> addedUsers_;
};

#endif // CREATEGROUPCHATCONTROLLER_H
