#include "../include/CreateGroupChatController.h"

CreateGroupChatController::CreateGroupChatController(QObject* parent)
    : QObject(parent)
    , usersModel_(new UsersModel(this))
{
}

CreateGroupChatController::~CreateGroupChatController()
{
}

void CreateGroupChatController::getUsers()
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString requestInfo_ = "Get_Users_On_Server_For_Add_User_In_Chat";
    QString request_ = jsonWorker_.createJsonGetUsersOnServer(requestInfo_, serverId_);

    emit getUsersOnServerSignal(request_);
}

UsersModel* CreateGroupChatController::getUsersModel()
{
    return usersModel_;
}

void CreateGroupChatController::saveAvatarAndName(const QString& q_groupAvatar, const QString& q_groupName)
{
    if(q_groupAvatar != "")
    {
        receivedGroupAvatar_ = imageWorker_.encodeImage(q_groupAvatar);
    }
    receivedGroupName_ = q_groupName;
}

void CreateGroupChatController::slotSetUsersOnServerPreparing(const QJsonObject& jsonObj_)
{
    int serverId_ = jsonObj_["serverId"].toInt();

    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        QJsonArray array_ = jsonObj_["users"].toArray();

        for(const auto& i : array_)
        {
            if(!i.isObject())
            {
                continue;
            }

            QJsonObject userObject_ = i.toObject();

            int userId_ = userObject_["userId"].toInt();

            if(userId_ == UserAccountManager::instance().getUserId())
            {
                continue;
            }

            QImage image_ = imageWorker_.decodeImage(userObject_["avatar"].toString());

            QString firstName_ = userObject_["firstName"].toString();
            QString lastName_ = userObject_["lastName"].toString();
            QString middleName_ = userObject_["middleName"].toString();
            bool isServerAdmin_ = userObject_["isServerAdmin"].toBool();
            bool isGlobalAdmin_ = userObject_["isGlobalAdmin"].toBool();

            usersModel_->addUserForSelect(serverId_, image_, userId_, firstName_, lastName_, middleName_, isServerAdmin_, isGlobalAdmin_);
        }
    }
}

void CreateGroupChatController::slotCodeProcessing(const QString& code_)
{
    if(code_ == "ERROR")
    {
        emit codeErrorSignal();
    }
    else if(code_ == "ACCESS_DENIED")
    {
        emit codeAccessDeniedSignal();
    }
    else if(code_ == "GROUP_NAME_EXISTS")
    {
        emit codeGroupNameExistsSignal();
    }
    else
    {
        emit codeGroupCreatedSignal();
    }
}

void CreateGroupChatController::addUser(const int userId_)
{
    addedUsers_.push_back(userId_);
}

void CreateGroupChatController::removeUser(const int userId_)
{
    addedUsers_.removeOne(userId_);
}

void CreateGroupChatController::createChat()
{
    if(addedUsers_.size() == 0)
    {
        emit noUsersSignal();
        return;
    }

    int serverId_ = SelectedServerManager::instance().getServerId();
    int userId_ = UserAccountManager::instance().getUserId();
    addedUsers_.push_back(userId_);

    qDebug() << serverId_ << ' ' << userId_;

    for(auto& i : addedUsers_)
    {
        qDebug() << "u = " << i;
    }

    QString request_ = jsonWorker_.createJsonCreateGroupChat(serverId_, userId_, receivedGroupAvatar_, receivedGroupName_, addedUsers_);
    emit createGroupChatSignal(request_);
}
