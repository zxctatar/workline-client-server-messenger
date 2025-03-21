#include "../../../include/SelectedServerManager.h"

SelectedServerManager::SelectedServerManager(QObject* parent)
    : QObject(parent)
    , serverId_(-1)
{
}

SelectedServerManager::~SelectedServerManager()
{
}

SelectedServerManager& SelectedServerManager::instance()
{
    static SelectedServerManager instance;
    return instance;
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
