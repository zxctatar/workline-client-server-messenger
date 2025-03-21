#include "../include/TopBarController.h"

TopBarController::TopBarController(QObject* parent)
    : QObject(parent)
    , profilePageController_(nullptr)
    , applicationPageController_(nullptr)
    , addUserController_(nullptr)
{
}

TopBarController::~TopBarController()
{
    deleteProfilePageController();
    deleteApplicationPageController();
    deleteAddUserOnServerController();
}

void TopBarController::deleteProfilePageController()
{
    if(profilePageController_)
    {
        profilePageController_.reset();
    }
}

void TopBarController::deleteApplicationPageController()
{
    if(applicationPageController_)
    {
        applicationPageController_.reset();
    }
}

void TopBarController::deleteAddUserOnServerController()
{
    if(addUserController_)
    {
        addUserController_.reset();
    }
}

void TopBarController::checkServerSelected()
{
    bool selected = SelectedServerManager::instance().getServerSelected();

    if(selected)
    {
        emit serverSelectedSignal();
    }
}

void TopBarController::getUserRole() const
{
    QString userRole_ = UserAccountManager::instance().getUserRole();

    emit setUserRoleSignal(userRole_);
}

ProfilePageController* TopBarController::getProfilePageController()
{
    if(!profilePageController_)
    {
        createProfilePageController();
    }
    return profilePageController_.get();
}

ApplicationPageController* TopBarController::getApplicationPageController()
{
    if(!applicationPageController_)
    {
        createApplicationPageController();
    }
    return applicationPageController_.get();
}

AddUserOnServerController* TopBarController::getAddUserController()
{
    if(!addUserController_)
    {
        createAddUserOnServerController();
    }
    return addUserController_.get();
}

void TopBarController::createProfilePageController()
{
    if(!profilePageController_)
    {
        profilePageController_ = std::make_shared<ProfilePageController>();
    }
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

void TopBarController::createAddUserOnServerController()
{
    if(!addUserController_)
    {
        addUserController_ = std::make_shared<AddUserOnServerController>();
    }
}
