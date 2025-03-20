#include "../../../include/UserModel.h"

UserModel::UserModel(QObject* parent)
    : QObject(parent)
    , id_(0)
    , isAuthorized(false)
{
}

UserModel::~UserModel()
{
}

void UserModel::setUserData(const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_)
{
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

QString UserModel::getUserRole() const
{
    return userRole_;
}

bool UserModel::getAuthorized() const
{
    return isAuthorized;
}

QString UserModel::getUserLogin() const
{
    return userLogin_;
}

QString UserModel::getUserPassword() const
{
    return userPassword_;
}

QString UserModel::getUserFirstName() const
{
    return userFirstName_;
}

QString UserModel::getUserLastName() const
{
    return userLastName_;
}

QString UserModel::getUserMiddleName() const
{
    return userMiddleName_;
}

QString UserModel::getUserEmail() const
{
    return userEmail_;
}

QString UserModel::getUserPhoneNumber() const
{
    return userPhoneNumber_;
}


// void UserModel::setIdSlot(const int received_id_)
// {
//     id_ = received_id_;
// }

// void UserModel::setUserRoleSlot(const std::string& userRole_)
// {
//     this->userRole_ = userRole_;
// }
