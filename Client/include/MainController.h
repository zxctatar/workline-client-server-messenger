#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <qqml.h>

#include "LoginPageController.h"
#include "RegistrationPageController.h"
#include "ServerConnector.h"
#include "ServerTableController.h"
#include "TopBarController.h"
#include "ChatsBarController.h"
#include "UserAccountManager.h"
#include "ChatHistoryController.h"
#include "SelectedChatManager.h"
#include "ImageWorker.h"

class MainController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(LoginPageController* loginPageController READ getLoginPageController NOTIFY loginPageControllerChanged FINAL)
    Q_PROPERTY(RegistrationPageController* regPageController READ getRegPageController NOTIFY regPageControllerChanged FINAL)
    Q_PROPERTY(ServerTableController* serverTableController READ getServerTableController NOTIFY serverTableControllerChanged FINAL)
    Q_PROPERTY(TopBarController* topBarController READ getTopBarController NOTIFY topBarControllerChanged FINAL)
    Q_PROPERTY(ChatsBarController* chatsBarController READ getChatsBarController NOTIFY chatsBarControllerChanged FINAL)
    Q_PROPERTY(ChatHistoryController* chatHistoryController READ getChatHistoryController NOTIFY chatHistoryControllerChanged FINAL)

public:
    explicit MainController(QObject* parent = nullptr);
    ~MainController();

    Q_INVOKABLE MainController* getMainController();

    Q_INVOKABLE LoginPageController* getLoginPageController();
    Q_INVOKABLE RegistrationPageController* getRegPageController();
    Q_INVOKABLE ServerTableController* getServerTableController();
    Q_INVOKABLE TopBarController* getTopBarController();
    Q_INVOKABLE ChatsBarController* getChatsBarController();
    Q_INVOKABLE ChatHistoryController* getChatHistoryController();

signals:
    void loginPageControllerChanged();
    void regPageControllerChanged();
    void serverTableControllerChanged();
    void topBarControllerChanged();
    void chatsBarControllerChanged();
    void chatHistoryControllerChanged();

private:
    void createLoginPageController();
    void createRegPageController();
    void createServerTableController();
    void createTopBarController();
    void createChatsBarController();
    void createChatHistoryController();

    ServerConnector* serverConnector_;
    LoginPageController* loginPageController_;
    RegistrationPageController* regPageController_;
    ServerTableController* serverTableController_;
    TopBarController* topBarController_;
    ChatsBarController* chatsBarController_;
    ChatHistoryController* chatHistoryController_;

    ImageWorker imageWorker_;
};

#endif // MAINCONTROLLER_H
