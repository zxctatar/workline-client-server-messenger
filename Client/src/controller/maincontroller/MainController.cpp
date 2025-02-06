#include "../../../include/MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , userModel_(new UserModel(this))
{
    serverConnector_ = (new ServerConnector("localhost", 8001, this));
    connect(serverConnector_, &ServerConnector::setUserId, userModel_, &UserModel::setId);
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

void MainController::createLoginPageController()
{
    if(!loginPageController_)
    {
        loginPageController_ = new LoginPageController(*serverConnector_, this);
    }
}

void MainController::createRegPageController()
{
    if(!regPageController_)
    {
        regPageController_ = new RegistrationPageController(*serverConnector_, this);
    }
}

