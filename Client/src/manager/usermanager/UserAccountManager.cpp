#include "../../../include/UserAccountManager.h"

UserAccountManager::UserAccountManager(QObject* parent)
    : QObject(parent)
    , id_(0)
    , isAuthorized(false)
{
}

UserAccountManager& UserAccountManager::instance()
{
    static UserAccountManager instance_;
    return instance_;
}

UserAccountManager::~UserAccountManager()
{
}

void UserAccountManager::setUserData(const QString& receivedUserAvatar_, const QString& receivedBirthDate_, const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_)
{
    userAvatarPath_ = receivedUserAvatar_;
    userBirthDate_ = receivedBirthDate_;
    userFirstName_ = receivedUserFirstName_;
    userLastName_ = receivedUserLastName_;
    userMiddleName_ = receivedUserMiddleName_;
    userEmail_ = receivedUserEmail_;
    userPhoneNumber_ = receivedUserPhoneNumber_;
    userLogin_ = receivedUserLogin_;
    userPassword_ = receivedUserPassword_;
    id_ = receivedUserId_;
    userRole_ = receivedUserRole_;

    isAuthorized = true;
}

QString UserAccountManager::getUserRole() const
{
    return userRole_;
}

bool UserAccountManager::getAuthorized() const
{
    return isAuthorized;
}

QString UserAccountManager::getUserAvatarPath() const
{
    return userAvatarPath_;
}

QString UserAccountManager::getUserBirthDate() const
{
    return userBirthDate_;
}

QString UserAccountManager::getUserLogin() const
{
    return userLogin_;
}

QString UserAccountManager::getUserPassword() const
{
    return userPassword_;
}

QString UserAccountManager::getUserFirstName() const
{
    return userFirstName_;
}

QString UserAccountManager::getUserLastName() const
{
    return userLastName_;
}

QString UserAccountManager::getUserMiddleName() const
{
    return userMiddleName_;
}

QString UserAccountManager::getUserEmail() const
{
    return userEmail_;
}

QString UserAccountManager::getUserPhoneNumber() const
{
    return userPhoneNumber_;
}
int UserAccountManager::getUserId() const
{
    return id_;
}
