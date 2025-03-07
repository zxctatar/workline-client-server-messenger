#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <qqml.h>

#include "LoginPageController.h"
#include "RegistrationPageController.h"
#include "ServerConnector.h"
#include "UserModel.h"
#include "ServerTableController.h"

class MainController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(LoginPageController* loginPageController READ getLoginPageController NOTIFY loginPageControllerChanged FINAL)
    Q_PROPERTY(RegistrationPageController* regPageController READ getRegPageController NOTIFY regPageControllerChanged FINAL)
    Q_PROPERTY(ServerTableController* serverTableController READ getServerTableController NOTIFY serverTableControllerChanged FINAL)

public:
    explicit MainController(QObject* parent = nullptr);
    ~MainController();

    Q_INVOKABLE MainController* getMainController();

    Q_INVOKABLE LoginPageController* getLoginPageController();
    Q_INVOKABLE RegistrationPageController* getRegPageController();
    Q_INVOKABLE ServerTableController* getServerTableController();

signals:
    void loginPageControllerChanged();
    void regPageControllerChanged();
    void serverTableControllerChanged();

private:
    void createLoginPageController();
    void createRegPageController();
    void createServerTableController();

    UserModel* userModel_;
    ServerConnector* serverConnector_;
    LoginPageController* loginPageController_;
    RegistrationPageController* regPageController_;
    ServerTableController* serverTableController_;
};

#endif // MAINCONTROLLER_H
