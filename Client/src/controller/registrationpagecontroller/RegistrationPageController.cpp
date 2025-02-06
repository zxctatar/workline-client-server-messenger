#include "../../../include/RegistrationPageController.h"

RegistrationPageController::RegistrationPageController(ServerConnector& serverConnector_, QObject* parent)
    : QObject(parent)
    , serverConnector_(serverConnector_)
{

}

RegistrationPageController::~RegistrationPageController()
{
}

void RegistrationPageController::emitSignal()
{
    emit mySignal();
}

void RegistrationPageController::prepareRegistrationRequest(const QString& q_initials, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& q_password) const
{
}
