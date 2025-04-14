#include "../../../include/SelectedServerManager.h"

SelectedServerManager::SelectedServerManager(QObject* parent)
    : QObject(parent)
    , serverId_(-1)
    , role_(serverRole::none)
{
}

SelectedServerManager::~SelectedServerManager()
{
}

SelectedServerManager& SelectedServerManager::instance()
{
    static SelectedServerManager instance_;
    return instance_;
}

void SelectedServerManager::setServerData(const int receivedServerId_, const QString& receivedServerName_, const QString& receivedServerDescription_)
{
    serverId_ = receivedServerId_;
    serverName_ = receivedServerName_;
    serverDescription_ = receivedServerDescription_;
}

bool SelectedServerManager::getServerSelected()
{
    if(serverId_ == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int SelectedServerManager::getServerId()
{
    return serverId_;
}

serverRole SelectedServerManager::stringToRole(const QString& serverRole_)
{
    if(serverRole_ == "IS_ADMIN")
    {
        return serverRole::admin;
    }
    else if(serverRole_ == "IS_USER")
    {
        return serverRole::user;
    }

    return serverRole::none;
}

void SelectedServerManager::setServerRole(const QString& serverRole_)
{
    role_ = stringToRole(serverRole_);
}

void SelectedServerManager::setServerRole(const int serverRole_)
{
    switch (serverRole_) {
    case 0:
        role_ = serverRole::none;
        break;
    case 1:
        role_ = serverRole::user;
        break;
    case 2:
        role_ = serverRole::admin;
        break;
    default:
        role_ = serverRole::none;
        break;
    }
}

int SelectedServerManager::getServerRole()
{
    return static_cast<int>(role_);
}

void SelectedServerManager::slotSetServerRole(const QJsonObject& jsonObj_)
{
    int receivedServerId_ = jsonObj_["serverId"].toInt();

    if(receivedServerId_ == serverId_ && jsonObj_["code"].toString() != "ERROR")
    {
        setServerRole(jsonObj_["code"].toString());

        if(getServerRole() == 0)
        {
            emit deleteServerSignal(receivedServerId_);
        }
    }
}

void SelectedServerManager::slotNewServerRoleProcessing(const QJsonObject& jsonObj_)
{
    int receivedServerId_ = jsonObj_["serverId"].toInt();

    if(receivedServerId_ == serverId_ && jsonObj_["code"].toString() == "ADMIN_ADDED")
    {
        setServerRole(2);
        emit serverRoleChangedSignal();
    }
    else if(receivedServerId_ == serverId_ && jsonObj_["code"].toString() == "ADMIN_REMOVED")
    {
        setServerRole(1);
        emit serverRoleChangedSignal();
    }
}
