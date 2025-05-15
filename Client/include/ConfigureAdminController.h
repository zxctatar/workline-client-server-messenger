#ifndef CONFIGUREADMINCONTROLLER_H
#define CONFIGUREADMINCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "UsersModel.h"
#include "SelectedServerManager.h"
#include "UserAccountManager.h"
#include "JsonWorker.h"
#include "ImageWorker.h"

class ConfigureAdminController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ConfigureAdminController(QObject* parent = nullptr);
    ~ConfigureAdminController();

    Q_INVOKABLE UsersModel* getUsersModel();
    Q_INVOKABLE void getUsersOnServer() const;
    Q_INVOKABLE void sendAddAdmin(const int serverId_, const int userId_) const;
    Q_INVOKABLE void sendRemoveAdmin(const int serverId_, const int userId_) const;
    Q_INVOKABLE void refreshUsers() const;

signals:
    void getUsersOnServerSignal(const QString& info_) const;

    void sendAddAdminSignal(const QString& info_) const;
    void sendRemoveAdminSignal(const QString& info_) const;

public slots:
    void slotSetUsersOnServerPreparing(const QJsonObject& jsonObj_);
    void slotAddAdminOnServerPreparing(const QJsonObject& jsonObj_);
    void slotRemoveAdminOnServerPreparing(const QJsonObject& jsonObj_);

private:
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;

    std::shared_ptr<UsersModel> usersModel_;
};

#endif // CONFIGUREADMINCONTROLLER_H
