#include "../../../include/RegistrationPageController.h"

RegistrationPageController::RegistrationPageController(ServerConnector& serverConnector_, QObject* parent)
    : QObject(parent)
    , serverConnector_(serverConnector_)
{
}

RegistrationPageController::~RegistrationPageController()
{
}
