#include "../../../include/LoginPageController.h"

LoginPageController::LoginPageController(QObject* parent)
    : QObject(parent)
{
}

LoginPageController::~LoginPageController()
{

}

void LoginPageController::prepareLoginRequest(const QString& q_login, const QString& q_password) const
{
    QString request_ = jsonWorker_.createJsonLogin(q_login, q_password);

    emit loginRequestSignal(request_);
}

void LoginPageController::slotResponseProcessing(const QJsonObject& jsonObj_) const
{
    if(jsonObj_["Code"].toString() == "INCORRECT_DATA")
    {
        emit incorrectDataSignal();
    }
    else if(jsonObj_["Code"].toString() == "ACCESS_ALLOWED_ADMIN" || jsonObj_["Code"].toString() == "ACCESS_ALLOWED_USER")
    {
        QString firstName_ = jsonObj_["UserFirstName"].toString();
        QString lastName_ = jsonObj_["UserLastName"].toString();
        QString middleName_ = jsonObj_["UserMiddleName"].toString();
        QString email_ = jsonObj_["UserEmail"].toString();
        QString phoneNumber_ = jsonObj_["UserPhoneNumber"].toString();
        QString login_ = jsonObj_["UserLogin"].toString();
        QString password_ = jsonObj_["UserPassword"].toString();
        int userId_ = jsonObj_["UserId"].toInt();
        QString userRole_ = jsonObj_["UserRole"].toString();

        UserAccountManager::instance().setUserData(firstName_, lastName_, middleName_, email_, phoneNumber_, login_, password_, userId_, userRole_);

        emit accessAllowedSignal();
    }
    else if(jsonObj_["Code"].toString() == "ACCESS_DENIED")
    {
        emit accessDeniedSignal();
    }
    else if(jsonObj_["Code"].toString() == "ERROR")
    {
        emit errorLoginSignal();
    }
}
