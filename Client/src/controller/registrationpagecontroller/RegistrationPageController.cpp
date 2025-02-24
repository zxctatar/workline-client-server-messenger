#include "../../../include/RegistrationPageController.h"
#include <QStringList>

RegistrationPageController::RegistrationPageController(ServerConnector& serverConnector_, QObject* parent)
    : QObject(parent)
    , serverConnector_(serverConnector_)
{

}

RegistrationPageController::~RegistrationPageController()
{
}

void RegistrationPageController::prepareRegistrationRequest(const QString& q_initials, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& q_password) const
{
    QStringList strList_ = q_initials.split(' ');
    QString lastname_ = strList_[0];
    QString firstname_ = strList_[1];
    QString middlename_ = strList_[2];

    QString request_ = jsonWorker_.createJsonRegistration(lastname_, firstname_, middlename_, q_login, q_phoneNumber, q_email, q_password);

    emit registrationRequestSignal(request_);
}

void RegistrationPageController::codeProcessing(const QString& code_) const
{
    if(code_ == "LOGIN_EXISTS")
    {
        emit loginExistsSignal();
    }
    else if(code_ == "PHONE_NUMBER_EXISTS")
    {
        emit phoneNumberExistsSignal();
    }
    else if(code_ == "EMAIL_EXISTS")
    {
        emit emailExistsSignal();
    }
    else if(code_ == "REG_OK")
    {
        emit regOkSignal();
    }
    else if(code_ == "ERROR")
    {
        emit errorRegSignal();
    }
}
