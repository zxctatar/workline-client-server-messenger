#include "../../../include/LoginPageController.h"

LoginPageController::LoginPageController(ServerConnector& serverConnector_, QObject* parent)
    : QObject(parent)
    , serverConnector_(serverConnector_)
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

void LoginPageController::codeProcessing(const QString& code_) const
{
    if(code_ == "INCORRECT_DATA")
    {
        emit incorrectDataSignal();
    }
    else if(code_ == "ACCESS_ALLOWED")
    {
        emit accessAllowedSignal();
    }
    else if(code_ == "ACCESS_DENIED")
    {
        emit accessDeniedSignal();
    }
    else if(code_ == "ERROR")
    {
        emit errorLoginSignal();
    }
}
