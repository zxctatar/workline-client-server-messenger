#ifndef SELECTEDSERVERMANAGER_H
#define SELECTEDSERVERMANAGER_H

#include <QObject>
#include <qqml.h>
#include <QJsonObject>

enum class serverRole{none = 0, user, admin};

class SelectedServerManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    static SelectedServerManager& instance();

    void setServerData(const int receivedServerId_, const QString& receivedServerName_, const QString& receivedServerDescription_);
    bool getServerSelected();
    int getServerId();
    void setServerRole(const QString& serverRole_);
    void setServerRole(const int serverRole_);
    int getServerRole();

signals:
    void deleteServerSignal(const int serverId_);
    void serverRoleChangedSignal();

public slots:
    void slotSetServerRole(const QJsonObject& jsonObj_);
    void slotNewServerRoleProcessing(const QJsonObject& jsonObj_);

private:
    explicit SelectedServerManager(QObject* parent = nullptr);
    ~SelectedServerManager();

    serverRole stringToRole(const QString& serverRole_);

    int serverId_;
    QString serverName_;
    QString serverDescription_;
    serverRole role_;
};

#endif // SELECTEDSERVERMANAGER_H
