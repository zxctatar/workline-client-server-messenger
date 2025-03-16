#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <qqml.h>

#include "LoginPageController.h"
#include "RegistrationPageController.h"
#include "ServerConnector.h"
#include "ServerTableController.h"
#include "UserAccountController.h"
#include "TopBarController.h"

class MainController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(LoginPageController* loginPageController READ getLoginPageController NOTIFY loginPageControllerChanged FINAL)
    Q_PROPERTY(RegistrationPageController* regPageController READ getRegPageController NOTIFY regPageControllerChanged FINAL)
    Q_PROPERTY(ServerTableController* serverTableController READ getServerTableController NOTIFY serverTableControllerChanged FINAL)
    Q_PROPERTY(TopBarController* topBarController READ getTopBarController NOTIFY topBarControllerChanged FINAL)

public:
    explicit MainController(QObject* parent = nullptr);
    ~MainController();

    Q_INVOKABLE MainController* getMainController();

    Q_INVOKABLE LoginPageController* getLoginPageController();
    Q_INVOKABLE RegistrationPageController* getRegPageController();
    Q_INVOKABLE ServerTableController* getServerTableController();
    Q_INVOKABLE TopBarController* getTopBarController();

signals:
    void loginPageControllerChanged();
    void regPageControllerChanged();
    void serverTableControllerChanged();
    void topBarControllerChanged();

private:
    void createLoginPageController();
    void createRegPageController();
    void createServerTableController();
    void createTopBarController();

    UserAccountController* userAccountController_;
    ServerConnector* serverConnector_;
    LoginPageController* loginPageController_;
    RegistrationPageController* regPageController_;
    ServerTableController* serverTableController_;
    TopBarController* topBarController_;
};

#endif // MAINCONTROLLER_H
