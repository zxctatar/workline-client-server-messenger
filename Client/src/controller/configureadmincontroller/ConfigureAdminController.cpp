#include "../../../include/ConfigureAdminController.h"

ConfigureAdminController::ConfigureAdminController(QObject* parent)
    : QObject(parent)
    , usersModel_(std::make_shared<UsersModel>(this))
{
}

ConfigureAdminController::~ConfigureAdminController()
{
    if(usersModel_)
    {
        usersModel_.reset();
    }
}

UsersModel* ConfigureAdminController::getUsersModel()
{
    return usersModel_.get();
}

void ConfigureAdminController::getUsersOnServer() const
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetUsersOnServer(serverId_);

    emit getUsersOnServerSignal(request_);
}

void ConfigureAdminController::slotSetUsersOnServerPreparing(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();

    QJsonArray jsonArray_ = jsonObj_["users"].toArray();

    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        for(const auto& i : jsonArray_)
        {
            if(!i.isObject())
            {
                continue;
            }

            QJsonObject userObject_ = i.toObject();

            int userId_ = userObject_["userId"].toInt();
            QString firstName_ = userObject_["firstName"].toString();
            QString lastName_ = userObject_["lastName"].toString();
            QString middleName_ = userObject_["middleName"].toString();
            bool isServerAdmin_ = userObject_["isServerAdmin"].toBool();
            bool isGlobalAdmin_ = userObject_["isGlobalAdmin"].toBool();

            usersModel_->addUser(serverId_, userId_, firstName_, lastName_, middleName_, isServerAdmin_, isGlobalAdmin_);
        }
    }
}

void ConfigureAdminController::sendAddAdmin(const int serverId_, const int userId_) const
{
    QString request_ = jsonWorker_.createJsonAddAdminOnServer(serverId_, userId_);
    emit sendAddAdminSignal(request_);
}

void ConfigureAdminController::sendRemoveAdmin(const int serverId_, const int userId_) const
{
    QString request_ = jsonWorker_.createJsonRemoveAdminOnServer(serverId_, userId_);
    emit sendRemoveAdminSignal(request_);
}

void ConfigureAdminController::slotAddAdminOnServerPreparing(const QJsonObject& jsonObj_)
{
    int userId_ = jsonObj_["userId"].toInt();
    int serverId_ = jsonObj_["serverId"].toInt();

    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        usersModel_->addAdminRole(userId_, serverId_);
    }
}

void ConfigureAdminController::slotRemoveAdminOnServerPreparing(const QJsonObject& jsonObj_)
{
    int userId_ = jsonObj_["userId"].toInt();
    int serverId_ = jsonObj_["serverId"].toInt();

    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        usersModel_->removeAdminRole(userId_, serverId_);
    }
}

void ConfigureAdminController::refreshUsers() const
{
    usersModel_->clearUsers();
    getUsersOnServer();
}
