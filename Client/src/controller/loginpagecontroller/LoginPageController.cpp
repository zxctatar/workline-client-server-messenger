#include "../../../include/LoginPageController.h"

LoginPageController::LoginPageController(ServerConnector& serverConnector_, QObject* parent)
    : QObject(parent)
    , serverConnector_(serverConnector_)
{
}

LoginPageController::~LoginPageController()
{
}
