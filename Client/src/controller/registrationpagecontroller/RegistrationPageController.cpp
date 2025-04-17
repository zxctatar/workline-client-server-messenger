#include "../../../include/RegistrationPageController.h"
#include <QStringList>

RegistrationPageController::RegistrationPageController(QObject* parent)
    : QObject(parent)
{

}

RegistrationPageController::~RegistrationPageController()
{
}

void RegistrationPageController::prepareRegistrationRequest(const QString& q_image, const QString& q_initials, const QString& q_birthDate, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& q_password) const
{
    QStringList strList_ = q_initials.split(' ');
    QString lastname_ = strList_[0];
    QString firstname_ = strList_[1];
    QString middlename_ = strList_[2];

    QString image_ = imageWorker_.encodeImage(q_image);

    QString request_ = jsonWorker_.createJsonRegistration(image_, lastname_, firstname_, middlename_, q_birthDate, q_login, q_phoneNumber, q_email, q_password);

    emit registrationRequestSignal(request_);
}

void RegistrationPageController::slotCodeProcessing(const QString& code_) const
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
