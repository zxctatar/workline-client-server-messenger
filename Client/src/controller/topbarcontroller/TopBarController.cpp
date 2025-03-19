#include "../include/TopBarController.h"

TopBarController::TopBarController(QObject* parent)
    : QObject(parent)
    , applicationPageController_(nullptr)
{
}

TopBarController::~TopBarController()
{
    if(applicationPageController_)
    {
        delete applicationPageController_;
    }
}

void TopBarController::getUserRole() const
{
    emit needUserRoleSignal();
}

void TopBarController::getUserData() const
{
    emit needUserDataSignal();
}

void TopBarController::slotSetUserRole(const QString& userRole_) const
{
    emit setUserRoleSignal(userRole_);
}

void TopBarController::slotSetUserData(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const
{
    emit setUserDataSignal(userFirstName_, userLastName_, userMiddleName_, userEmail_, userPhoneNumber_);
}

ApplicationPageController* TopBarController::getApplicationPageController()
{
    if(!applicationPageController_)
    {
        createApplicationPageController();
        connect(applicationPageController_, &ApplicationPageController::getUnverUsersSignal, this, &TopBarController::handOverGetUnverUsersSignal);
        connect(this, &TopBarController::handOverReceivedUnverUsersSignal, applicationPageController_, &ApplicationPageController::slotUnverUsersProcessing);
        connect(applicationPageController_, &ApplicationPageController::approveUserSignal, this, &TopBarController::handOverApproveUserSignal);
        connect(applicationPageController_, &ApplicationPageController::rejectUserSignal, this, &TopBarController::handOverRejectUserSignal);
        connect(this, &TopBarController::handOverReceivedApproveUserSignal, applicationPageController_, &ApplicationPageController::slotApproveUserProcessing);
        connect(this, &TopBarController::handOverReceivedRejectUserSignal, applicationPageController_, &ApplicationPageController::slotRejectUserProcessing);
        connect(this, &TopBarController::handOverDeleteUnverUserSignal, applicationPageController_, &ApplicationPageController::slotDeleteUnverUser);
    }
    return applicationPageController_;
}

void TopBarController::createApplicationPageController()
{
    if(!applicationPageController_)
    {
        applicationPageController_ = new ApplicationPageController(this);
    }
}
