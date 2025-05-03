#include "../include/TopBarController.h"

TopBarController::TopBarController(QObject* parent)
    : QObject(parent)
    , profilePageController_(nullptr)
    , applicationPageController_(nullptr)
    , addUserController_(nullptr)
    , configureAdminController_(nullptr)
    , createGroupChatController_(nullptr)
{
}

TopBarController::~TopBarController()
{
    deleteProfilePageController();
    deleteApplicationPageController();
    deleteAddUserOnServerController();
    deleteConfigureAdminController();
    deleteCreateGroupChatController();
}

void TopBarController::slotSetNewServerRole()
{
    if(UserAccountManager::instance().getUserRole() != "admin")
    {
        int serverRole_ = SelectedServerManager::instance().getServerRole();

        emit setServerRoleSignal(serverRole_);
    }
}

void TopBarController::getServerRole()
{
    if(UserAccountManager::instance().getUserRole() != "admin")
    {
        int serverRole_ = SelectedServerManager::instance().getServerRole();

        emit setServerRoleSignal(serverRole_);
    }
}

void TopBarController::accessToServerDenied(const int serverId_)
{
    emit accessToServerDeniedSignal(serverId_);
}

void TopBarController::getServerId()
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    emit setServerId(serverId_);
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

void TopBarController::deleteConfigureAdminController()
{
    if(configureAdminController_)
    {
        configureAdminController_.reset();
    }
}

void TopBarController::deleteCreateGroupChatController()
{
    if(createGroupChatController_)
    {
        createGroupChatController_.reset();
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

ConfigureAdminController* TopBarController::getConfigureAdminController()
{
    if(!configureAdminController_)
    {
        createConfigureAdminController();
    }
    return configureAdminController_.get();
}

CreateGroupChatController* TopBarController::getCreateGroupChatController()
{
    if(!createGroupChatController_)
    {
        createCreateGroupChatController();
    }
    return createGroupChatController_.get();
}

void TopBarController::createProfilePageController()
{
    if(!profilePageController_)
    {
        profilePageController_ = std::make_shared<ProfilePageController>(this);
    }
}

void TopBarController::createApplicationPageController()
{
    if(!applicationPageController_)
    {
        applicationPageController_ = std::make_shared<ApplicationPageController>(this);

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
        addUserController_ = std::make_shared<AddUserOnServerController>(this);

        connect(addUserController_.get(), &AddUserOnServerController::getCandidateUsersSignal, this, &TopBarController::handOverGetCandidateUsersSignal);
        connect(this, &TopBarController::handOverReceivedCandidateUsersSignal, addUserController_.get(), &AddUserOnServerController::slotCandidateUsersProcessing);
        connect(addUserController_.get(), &AddUserOnServerController::requestAddUserSignal, this, &TopBarController::handOverRequestAddUserSignal);
        connect(this, &TopBarController::handOverAddUserOnServerSignal, addUserController_.get(), &AddUserOnServerController::slotAddUserOnServerProccessing);
        connect(this, &TopBarController::handOverDeleteUserOnServerSignal, addUserController_.get(), &AddUserOnServerController::slotDeleteUserOnServer);
    }
}

void TopBarController::createConfigureAdminController()
{
    if(!configureAdminController_)
    {
        configureAdminController_ = std::make_shared<ConfigureAdminController>(this);
        connect(configureAdminController_.get(), &ConfigureAdminController::getUsersOnServerSignal, this, &TopBarController::handOverGetUsersOnServerSignal);
        connect(this, &TopBarController::handOverSendUsersOnServerForConfigureAdminSignal, configureAdminController_.get(), &ConfigureAdminController::slotSetUsersOnServerPreparing);
        connect(configureAdminController_.get(), &ConfigureAdminController::sendAddAdminSignal, this, &TopBarController::handOverAddAdminOnServerSignal);
        connect(configureAdminController_.get(), &ConfigureAdminController::sendRemoveAdminSignal, this, &TopBarController::handOverRemoveAdminOnServerSignal);
        connect(this, &TopBarController::handOverResponseAddAdminOnServerSignal, configureAdminController_.get(), &ConfigureAdminController::slotAddAdminOnServerPreparing);
        connect(this, &TopBarController::handOverResponseRemoveAdminOnServerSignal, configureAdminController_.get(), &ConfigureAdminController::slotRemoveAdminOnServerPreparing);
    }
}

void TopBarController::createCreateGroupChatController()
{
    if(!createGroupChatController_)
    {
        createGroupChatController_ = std::make_shared<CreateGroupChatController>(this);
        connect(this, &TopBarController::handOverSendUsersOnServerForAddUserInChatSignal, createGroupChatController_.get(), &CreateGroupChatController::slotSetUsersOnServerPreparing);
        connect(createGroupChatController_.get(), &CreateGroupChatController::getUsersOnServerSignal, this, &TopBarController::handOverGetUsersOnServerSignal);
        connect(createGroupChatController_.get(), &CreateGroupChatController::createGroupChatSignal, this, &TopBarController::handOverCreateGroupChatSignal);
        connect(this, &TopBarController::handOverCodeCreateGroupChatSignal, createGroupChatController_.get(), &CreateGroupChatController::slotCodeProcessing);
    }
}
