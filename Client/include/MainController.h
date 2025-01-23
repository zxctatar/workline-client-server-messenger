#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <qqml.h>

#include "LoginPageController.h"
#include "RegistrationPageController.h"
#include "ServerConnector.h"

class MainController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit MainController(ServerConnector& serverConnector, QObject* parent = nullptr);
    ~MainController();

    Q_INVOKABLE LoginPageController* getLoginPageController();
    Q_INVOKABLE RegistrationPageController* getRegPageController();

private:
    void createLoginPageController();
    void createRegPageController();

    LoginPageController* loginPageController_;
    RegistrationPageController* regPageController_;
    ServerConnector& serverConnector_;
};

#endif // MAINCONTROLLER_H
