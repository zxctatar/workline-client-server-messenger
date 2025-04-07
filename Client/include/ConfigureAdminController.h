#ifndef CONFIGUREADMINCONTROLLER_H
#define CONFIGUREADMINCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "UsersModel.h"
#include "SelectedServerManager.h"
#include "JsonWorker.h"

class ConfigureAdminController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ConfigureAdminController(QObject* parent = nullptr);
    ~ConfigureAdminController();

    Q_INVOKABLE UsersModel* getUsersModel();
    Q_INVOKABLE void getServerId() const;
    Q_INVOKABLE void getUsersOnServer() const;

signals:
    void setServerIdSignal(const int serverId_) const;
    void getUsersOnServerSignal(const QString& info_) const;

public slots:
    void slotSetUsersOnServerPreparing(const QJsonObject& jsonObj_);

private:
    JsonWorker jsonWorker_;

    std::shared_ptr<UsersModel> usersModel_;
};

#endif // CONFIGUREADMINCONTROLLER_H
