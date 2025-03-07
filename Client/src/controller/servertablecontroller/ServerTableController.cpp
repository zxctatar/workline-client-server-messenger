#include "../../../include/ServerTableController.h"

ServerTableController::ServerTableController(QObject* parent)
    : QObject(parent)
    , serverModel_(new ServerModel(this))
{
}

ServerTableController::~ServerTableController()
{
}

ServerModel* ServerTableController::getServerModel() const
{
    return serverModel_;
}

void ServerTableController::getUserRole() const
{
    emit needUserRoleSignal();
}

void ServerTableController::slotSetUserRole(const QString& userRole_) const
{
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

        serverModel_->addServer(serverID_, serverName_, serverDescription_);
    }
}

void ServerTableController::slotCodeProcessing(const QJsonObject& jsonObj_) const
{
    if(jsonObj_["Code"].toString() == "SERVER_ADDED")
    {
        serverModel_->addServer(jsonObj_["ServerID"].toInt(), jsonObj_["ServerName"].toString(), jsonObj_["ServerDescription"].toString());
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
