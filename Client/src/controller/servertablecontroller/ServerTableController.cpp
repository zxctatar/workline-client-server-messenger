#include "../../../include/ServerTableController.h"

ServerTableController::ServerTableController(QObject* parent)
    : QObject(parent)
    , serverModel_(new ServerModel(this))
{
}

ServerTableController::~ServerTableController()
{
    if(serverModel_)
    {
        delete serverModel_;
    }
}

ServerModel* ServerTableController::getServerModel() const
{
    return serverModel_;
}

void ServerTableController::getUserRole() const
{
    QString userRole_ = UserAccountManager::instance().getUserRole();

    emit setUserRoleSignal(userRole_);
}

void ServerTableController::preparingAddServerRequest(const QString& q_serverName, const QString& q_serverDescription)
{
    QString request_ = jsonWorker_.createJsonAddServer(q_serverName, q_serverDescription);

    emit addServerSignal(request_);
}

void ServerTableController::getServers() const
{
    QString request_ = jsonWorker_.createJsonGetServers();

    emit needServers(request_);
}

void ServerTableController::setServerData(const int serverId_, const QString& serverName_, const QString& serverDescription_)
{
    SelectedServerManager::instance().setServerData(serverId_, serverName_, serverDescription_);
}

void ServerTableController::serverSelected(const int serverId_)
{
    if(UserAccountManager::instance().getUserRole() != "admin")
    {
        int userId_ = UserAccountManager::instance().getUserId();
        QString request_ = jsonWorker_.createJsonGetServerRole(userId_, serverId_);
        emit getServerRoleSignal(request_);
    }

    emit serverSelectedSignal(serverId_);
}

void ServerTableController::slotServerProcessing(const QJsonObject& jsonObj_) const
{
    QJsonArray serversArray_ = jsonObj_["Servers"].toArray();

    for(const QJsonValue& value : serversArray_)
    {
        if(!value.isObject())
        {
            continue;
        }

        QJsonObject serverObj_ = value.toObject();

        int serverID_ = serverObj_["id"].toInt();
        QString serverName_ = serverObj_["name"].toString();
        QString serverDescription_ = serverObj_["description"].toString();

        serverModel_->addServer(serverID_, serverName_[0], serverName_, serverDescription_);
    }
}

void ServerTableController::slotCodeProcessing(const QJsonObject& jsonObj_) const
{
    if(jsonObj_["Code"].toString() == "MY_SERVER_ADDED")
    {
        serverModel_->addServer(jsonObj_["ServerID"].toInt(), jsonObj_["ServerName"].toString()[0], jsonObj_["ServerName"].toString(), jsonObj_["ServerDescription"].toString());
        emit myServerAddedSignal();
    }
    else if(jsonObj_["Code"].toString() == "ADD_NEW_SERVER")
    {
        serverModel_->addServer(jsonObj_["ServerID"].toInt(), jsonObj_["ServerName"].toString()[0], jsonObj_["ServerName"].toString(), jsonObj_["ServerDescription"].toString());
    }
    else if(jsonObj_["Code"].toString() == "SERVER_NAME_EXISTS")
    {
        emit serverNameExistsSignal();
    }
    else if(jsonObj_["Code"].toString() == "ERROR")
    {
        emit errorCreateServerSignal();
    }
}

void ServerTableController::slotDeleteServer(const int serverId_)
{
    int selectedServerId_ = SelectedServerManager::instance().getServerId();

    if(selectedServerId_ == serverId_)
    {
        SelectedServerManager::instance().setServerData(-1, "","");
        emit selectedServerDeletedSignal();
    }

    serverModel_->deleteServer(serverId_);
}

void ServerTableController::deleteServer(const int serverId_)
{
    QString request_ = jsonWorker_.createJsonDeleteServer(serverId_);
    emit deleteServerSignal(request_);
}

void ServerTableController::slotAddNewServer(const int serverId_, const QString& serverName_, const QString& serverDescription_)
{
    serverModel_->addServer(serverId_, serverName_[0] ,serverName_, serverDescription_);
}
