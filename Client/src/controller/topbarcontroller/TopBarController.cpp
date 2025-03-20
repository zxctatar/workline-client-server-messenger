#include "../include/TopBarController.h"

TopBarController::TopBarController(QObject* parent)
    : QObject(parent)
    , applicationPageController_(nullptr)
{
}

TopBarController::~TopBarController()
{
    deleteApplicationPageController();
}

void TopBarController::deleteApplicationPageController()
{
    if(applicationPageController_)
    {
        applicationPageController_.reset();
    }
}

void TopBarController::getUserRole() const
{
    QString userRole_ = UserAccountManager::instance().getUserRole();

    emit setUserRoleSignal(userRole_);
}

void TopBarController::getUserData() const
{
    QString userFirstName_ = UserAccountManager::instance().getUserFirstName();
    QString userLastName_ = UserAccountManager::instance().getUserLastName();
    QString userMiddleName_ = UserAccountManager::instance().getUserMiddleName();
    QString userEmail_ = UserAccountManager::instance().getUserEmail();
    QString userPhoneNumber_ = UserAccountManager::instance().getUserPhoneNumber();

    emit setUserDataSignal(userFirstName_, userLastName_, userMiddleName_, userEmail_, userPhoneNumber_);
}

ApplicationPageController* TopBarController::getApplicationPageController()
{
    if(!applicationPageController_)
    {
        createApplicationPageController();
    }
    return applicationPageController_.get();
}

void TopBarController::createApplicationPageController()
{
    if(!applicationPageController_)
    {
        applicationPageController_ = std::make_shared<ApplicationPageController>();

        connect(applicationPageController_.get(), &ApplicationPageController::getUnverUsersSignal, this, &TopBarController::handOverGetUnverUsersSignal);
        connect(this, &TopBarController::handOverReceivedUnverUsersSignal, applicationPageController_.get(), &ApplicationPageController::slotUnverUsersProcessing);
        connect(applicationPageController_.get(), &ApplicationPageController::approveUserSignal, this, &TopBarController::handOverApproveUserSignal);
        connect(applicationPageController_.get(), &ApplicationPageController::rejectUserSignal, this, &TopBarController::handOverRejectUserSignal);
        connect(this, &TopBarController::handOverReceivedApproveUserSignal, applicationPageController_.get(), &ApplicationPageController::slotApproveUserProcessing);
        connect(this, &TopBarController::handOverReceivedRejectUserSignal, applicationPageController_.get(), &ApplicationPageController::slotRejectUserProcessing);
        connect(this, &TopBarController::handOverDeleteUnverUserSignal, applicationPageController_.get(), &ApplicationPageController::slotDeleteUnverUser);
    }
}
