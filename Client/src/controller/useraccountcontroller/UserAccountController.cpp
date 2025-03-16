#include "../../../include/UserAccountController.h"

UserAccountController::UserAccountController(QObject* parent)
    : QObject(parent)
    , userModel_(new UserModel(this))
{
}

UserAccountController::~UserAccountController()
{
}

void UserAccountController::slotSetUserData(const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_)
{
    userModel_->setUserData(receivedUserFirstName_, receivedUserLastName_, receivedUserMiddleName_, receivedUserEmail_, receivedUserPhoneNumber_, receivedUserLogin_, receivedUserPassword_, receivedUserId_, receivedUserRole_);
}

void UserAccountController::slotSendUserRole()
{
    QString userRole_ = userModel_->getUserRole();

    emit sendUserRoleSignal(userRole_);
}

void UserAccountController::slotCheckAuthorization()
{
    if(userModel_->getAuthorized())
    {
        QString userLogin_ = userModel_->getUserLogin();
        QString userPassword_ = userModel_->getUserPassword();

        QString request_ = jsonWorker_.createJsonReconnect(userLogin_, userPassword_);

        emit sendAuthorizationDataSignal(request_);
    }
}

void UserAccountController::slotSendUserData()
{
    QString firstName_ = userModel_->getUserFirstName();
    QString lastName_ = userModel_->getUserLastName();
    QString middleName_ = userModel_->getUserMiddleName();
    QString email_ = userModel_->getUserEmail();
    QString phoneNumber_ = userModel_->getUserPhoneNumber();

    emit sendUserDataSignal(firstName_, lastName_, middleName_, email_, phoneNumber_);
}

