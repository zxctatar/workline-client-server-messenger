#include "../../../include/MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , userModel_(new UserModel(this))
{
    serverConnector_ = (new ServerConnector("localhost", 8001, this));
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
    if(userModel_)
    {
        delete userModel_;
    }
    if(serverConnector_)
    {
        delete serverConnector_;
    }
    if(serverTableController_)
    {
        delete serverTableController_;
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

void MainController::createLoginPageController()
{
    if(!loginPageController_)
    {
        loginPageController_ = new LoginPageController(this);
        connect(loginPageController_, &LoginPageController::loginRequestSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendLoginCodeSignal, loginPageController_, &LoginPageController::slotResponseProcessing);

        connect(loginPageController_, &LoginPageController::sendUserDataSignal, userModel_, &UserModel::slotSetUserData);
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
        connect(serverTableController_, &ServerTableController::needUserRoleSignal, userModel_, &UserModel::slotSendUserRole);
        connect(userModel_, &UserModel::sendUserRoleSignal, serverTableController_, &ServerTableController::slotSetUserRole);

        connect(serverTableController_, &ServerTableController::addServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendServerTableCodeSignal, serverTableController_, &ServerTableController::slotCodeProcessing);
        connect(serverTableController_, &ServerTableController::needServers, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUserServers, serverTableController_, &ServerTableController::slotServerProcessing);
    }
}
