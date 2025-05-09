#ifndef SERVERTABLECONTROLLER_H
#define SERVERTABLECONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "ServerModel.h"
#include "JsonWorker.h"
#include "ImageWorker.h"
#include "UserAccountManager.h"
#include "SelectedServerManager.h"

class ServerTableController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ServerTableController(QObject* parent = nullptr);
    ~ServerTableController();

    Q_INVOKABLE void getUserRole() const;
    Q_INVOKABLE ServerModel* getServerModel() const;
    Q_INVOKABLE void preparingAddServerRequest(const QString& q_base64Image, const QString& q_serverName, const QString& q_serverDescription);
    Q_INVOKABLE void getServers() const;
    Q_INVOKABLE void deleteServer(const int serverId_);
    Q_INVOKABLE void setServerData(const int serverId_, const QString& serverName_, const QString& serverDescription_);
    Q_INVOKABLE void serverSelected(const int serverId_);

signals:
    void needUserRoleSignal() const;
    void setUserRoleSignal(const QString& userRole_) const;

    void addServerSignal(const QString& info_) const;
    void deleteServerSignal(const QString& info_) const;
    void needServers(const QString& info_) const;

    void myServerAddedSignal() const;
    void serverNameExistsSignal() const;
    void errorCreateServerSignal() const;

    void getServerRoleSignal(const QString& info_) const;
    void serverSelectedSignal(const int serverId_) const;
    void selectedServerDeletedSignal() const;

public slots:
    void slotCodeProcessing(const QJsonObject& jsonObj_);
    void slotServerProcessing(const QJsonObject& jsonObj_);
    void slotDeleteServer(const int serverId_);
    void slotAddNewServer(const QJsonObject& jsonObj_);

private:

    ServerModel* serverModel_;
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
};

#endif // SERVERTABLECONTROLLER_H
