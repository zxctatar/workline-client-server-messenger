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

void ConfigureAdminController::getServerId() const
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    emit setServerIdSignal(serverId_);
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
