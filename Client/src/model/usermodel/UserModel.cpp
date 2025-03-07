#include "../../../include/UserModel.h"

UserModel::UserModel(QObject* parent)
    : QObject(parent)
    , id_(0)
{
}

UserModel::~UserModel()
{
}

void UserModel::slotSetUserData(const int receivedUserId_, const QString& receivedUserRole_)
{
    id_ = receivedUserId_;
    userRole_ = receivedUserRole_;
}

void UserModel::slotSendUserRole() const
{
    emit sendUserRoleSignal(userRole_);
}

// void UserModel::setIdSlot(const int received_id_)
// {
//     id_ = received_id_;
// }

// void UserModel::setUserRoleSlot(const std::string& userRole_)
// {
//     this->userRole_ = userRole_;
// }
