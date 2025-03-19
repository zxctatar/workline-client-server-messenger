#include "../../../include/MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , userAccountController_(new UserAccountController(this))
    , loginPageController_(nullptr)
    , regPageController_(nullptr)
    , serverConnector_(nullptr)
    , serverTableController_(nullptr)
    , topBarController_(nullptr)
{
    serverConnector_ = (new ServerConnector("localhost", 8001, this));

    connect(serverConnector_, &ServerConnector::checkAuthorizationSignal, userAccountController_, &UserAccountController::slotCheckAuthorization);
    connect(userAccountController_, &UserAccountController::sendAuthorizationDataSignal, serverConnector_, &ServerConnector::slotSendToServer);
}

MainController::~MainController()
{
    if(loginPageController_)
    {
        delete loginPageController_;
    }
    if(regPageController_)
    {
        delete regPageController_;
    }
    if(userAccountController_)
    {
        delete userAccountController_;
    }
    if(serverConnector_)
    {
        delete serverConnector_;
    }
    if(serverTableController_)
    {
        delete serverTableController_;
    }
    if(topBarController_)
    {
        delete topBarController_;
    }
}

MainController* MainController::getMainController()
{
    return this;
}

LoginPageController* MainController::getLoginPageController()
{
    if(!loginPageController_)
    {
        createLoginPageController();
    }
    return loginPageController_;
}

RegistrationPageController* MainController::getRegPageController()
{
    if(!regPageController_)
    {
        createRegPageController();
    }
    return regPageController_;
}

ServerTableController* MainController::getServerTableController()
{
    if(!serverTableController_)
    {
        createServerTableController();
    }
    return serverTableController_;
}

TopBarController* MainController::getTopBarController()
{
    if(!topBarController_)
    {
        createTopBarController();
    }
    return topBarController_;
}

void MainController::createLoginPageController()
{
    if(!loginPageController_)
    {
        loginPageController_ = new LoginPageController(this);
        connect(loginPageController_, &LoginPageController::loginRequestSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendLoginCodeSignal, loginPageController_, &LoginPageController::slotResponseProcessing);

        connect(loginPageController_, &LoginPageController::sendUserDataSignal, userAccountController_, &UserAccountController::slotSetUserData);
    }
}

void MainController::createRegPageController()
{
    if(!regPageController_)
    {
        regPageController_ = new RegistrationPageController(this);
        connect(regPageController_, &RegistrationPageController::registrationRequestSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendRegistrationCodeSignal, regPageController_, &RegistrationPageController::slotCodeProcessing);
    }
}

void MainController::createServerTableController()
{
    if(!serverTableController_)
    {
        serverTableController_ = new ServerTableController(this);
        connect(serverTableController_, &ServerTableController::needUserRoleSignal, userAccountController_, &UserAccountController::slotSendUserRole);
        connect(userAccountController_, &UserAccountController::sendUserRoleSignal, serverTableController_, &ServerTableController::slotSetUserRole);

        connect(serverTableController_, &ServerTableController::addServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverTableController_, &ServerTableController::deleteServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendDeleteServerId, serverTableController_, &ServerTableController::slotDeleteServer);
        connect(serverConnector_, &ServerConnector::sendServerTableCodeSignal, serverTableController_, &ServerTableController::slotCodeProcessing);
        connect(serverTableController_, &ServerTableController::needServers, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUserServers, serverTableController_, &ServerTableController::slotServerProcessing);
    }
}

void MainController::createTopBarController()
{
    if(!topBarController_)
    {
        topBarController_ = new TopBarController(this);
        connect(topBarController_, &TopBarController::needUserRoleSignal, userAccountController_, &UserAccountController::slotSendUserRole);
        connect(userAccountController_, &UserAccountController::sendUserRoleSignal, topBarController_, &TopBarController::slotSetUserRole);
        connect(topBarController_, &TopBarController::needUserDataSignal, userAccountController_, &UserAccountController::slotSendUserData);
        connect(userAccountController_, &UserAccountController::sendUserDataSignal, topBarController_, &TopBarController::slotSetUserData);

        connect(topBarController_, &TopBarController::handOverGetUnverUsersSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUnverUsers, topBarController_, &TopBarController::handOverReceivedUnverUsersSignal);
        connect(topBarController_, &TopBarController::handOverApproveUserSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(topBarController_, &TopBarController::handOverRejectUserSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendApproveUser, topBarController_, &TopBarController::handOverReceivedApproveUserSignal);
        connect(serverConnector_, &ServerConnector::sendRejectUser, topBarController_, &TopBarController::handOverReceivedRejectUserSignal);
        connect(serverConnector_, &ServerConnector::sendDeleteUnverUser, topBarController_, &TopBarController::handOverDeleteUnverUserSignal);
    }
}
