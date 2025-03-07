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
        emit sendUserDataSignal(jsonObj_["UserId"].toInt(), jsonObj_["UserRole"].toString());

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
