#include "../../../include/MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , loginPageController_(nullptr)
    , regPageController_(nullptr)
    , serverConnector_(nullptr)
    , serverTableController_(nullptr)
    , topBarController_(nullptr)
    , chatsBarController_(nullptr)
    , chatHistoryController_(nullptr)
    , chatInfoBarController_(nullptr)
{
    serverConnector_ = (new ServerConnector("localhost", 8001, this));

    connect(serverConnector_, &ServerConnector::sendServerRoleSignal, &SelectedServerManager::instance(), &SelectedServerManager::slotSetServerRole);
    connect(serverConnector_, &ServerConnector::sendServerRoleAddSignal, &SelectedServerManager::instance(), &SelectedServerManager::slotNewServerRoleProcessing);
    connect(serverConnector_, &ServerConnector::sendServerRoleRemovedSignal, &SelectedServerManager::instance(), &SelectedServerManager::slotNewServerRoleProcessing);
}

MainController::~MainController()
{
    if(loginPageController_)
    {
        loginPageController_->deleteLater();
    }
    if(regPageController_)
    {
        regPageController_->deleteLater();
    }
    if(serverConnector_)
    {
        serverConnector_->deleteLater();
    }
    if(serverTableController_)
    {
        serverTableController_->deleteLater();
    }
    if(topBarController_)
    {
        topBarController_->deleteLater();
    }
    if(chatsBarController_)
    {
        chatsBarController_->deleteLater();
    }
    if(chatInfoBarController_)
    {
        chatInfoBarController_->deleteLater();
    }

    imageWorker_.cleanupTempFiles();
}

MainController* MainController::getMainController()
{
    return this;
}

LoginPageController* MainController::getLoginPageController()
{
    if(!loginPageController_)
    {
        createLoginPageController();
    }
    return loginPageController_;
}

RegistrationPageController* MainController::getRegPageController()
{
    if(!regPageController_)
    {
        createRegPageController();
    }
    return regPageController_;
}

ServerTableController* MainController::getServerTableController()
{
    if(!serverTableController_)
    {
        createServerTableController();
    }
    return serverTableController_;
}

TopBarController* MainController::getTopBarController()
{
    if(!topBarController_)
    {
        createTopBarController();
    }
    return topBarController_;
}

ChatsBarController* MainController::getChatsBarController()
{
    if(!chatsBarController_)
    {
        createChatsBarController();
    }
    return chatsBarController_;
}

ChatHistoryController* MainController::getChatHistoryController()
{
    if(!chatHistoryController_)
    {
        createChatHistoryController();
    }
    return chatHistoryController_;
}

ChatInfoBarController* MainController::getChatInfoBarController()
{
    if(!chatInfoBarController_)
    {
        createChatInfoBarController();
    }
    return chatInfoBarController_;
}

void MainController::createLoginPageController()
{
    if(!loginPageController_)
    {
        loginPageController_ = new LoginPageController(this);
        connect(loginPageController_, &LoginPageController::loginRequestSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendLoginCodeSignal, loginPageController_, &LoginPageController::slotResponseProcessing);
    }
}

void MainController::createRegPageController()
{
    if(!regPageController_)
    {
        regPageController_ = new RegistrationPageController(this);
        connect(regPageController_, &RegistrationPageController::registrationRequestSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendRegistrationCodeSignal, regPageController_, &RegistrationPageController::slotCodeProcessing);
    }
}

void MainController::createServerTableController()
{
    if(!serverTableController_)
    {
        serverTableController_ = new ServerTableController(this);
        connect(serverTableController_, &ServerTableController::addServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverTableController_, &ServerTableController::deleteServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendDeleteServerIdSignal, serverTableController_, &ServerTableController::slotDeleteServer);
        connect(serverConnector_, &ServerConnector::sendServerTableCodeSignal, serverTableController_, &ServerTableController::slotCodeProcessing);
        connect(serverTableController_, &ServerTableController::needServers, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUserServersSignal, serverTableController_, &ServerTableController::slotServerProcessing);
        connect(serverConnector_, &ServerConnector::sendAddNewServerSignal, serverTableController_, &ServerTableController::slotAddNewServer);
        connect(serverTableController_, &ServerTableController::getServerRoleSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(&SelectedServerManager::instance(), &SelectedServerManager::deleteServerSignal, serverTableController_, &ServerTableController::slotDeleteServer);
        connect(serverTableController_, &ServerTableController::serverSelectedSignal, chatHistoryController_, &ChatHistoryController::slotServerChanged);
        connect(serverTableController_, &ServerTableController::serverSelectedSignal, chatInfoBarController_, &ChatInfoBarController::slotServerChanged);
    }
}

void MainController::createTopBarController()
{
    if(!topBarController_)
    {
        topBarController_ = new TopBarController(this);
        connect(serverTableController_, &ServerTableController::selectedServerDeletedSignal, topBarController_, &TopBarController::selectedServerDeletedSignal);
        connect(topBarController_, &TopBarController::handOverGetUnverUsersSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUnverUsersSignal, topBarController_, &TopBarController::handOverReceivedUnverUsersSignal);
        connect(topBarController_, &TopBarController::handOverApproveUserSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(topBarController_, &TopBarController::handOverRejectUserSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendApproveUserSignal, topBarController_, &TopBarController::handOverReceivedApproveUserSignal);
        connect(serverConnector_, &ServerConnector::sendRejectUserSignal, topBarController_, &TopBarController::handOverReceivedRejectUserSignal);
        connect(serverConnector_, &ServerConnector::sendDeleteUnverUserSignal, topBarController_, &TopBarController::handOverDeleteUnverUserSignal);
        connect(topBarController_, &TopBarController::handOverGetCandidateUsersSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendCandidateUsersSignal, topBarController_, &TopBarController::handOverReceivedCandidateUsersSignal);
        connect(topBarController_, &TopBarController::handOverRequestAddUserSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendAddUserOnServerSignal, topBarController_, &TopBarController::handOverAddUserOnServerSignal);
        connect(serverConnector_, &ServerConnector::sendDeleteUserOnServerSignal, topBarController_, &TopBarController::handOverDeleteUserOnServerSignal);
        connect(topBarController_, &TopBarController::handOverGetUsersOnServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendUsersOnServerSignal, topBarController_, &TopBarController::handOverSendUsersOnServerSignal);
        connect(topBarController_, &TopBarController::handOverAddAdminOnServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(topBarController_, &TopBarController::handOverRemoveAdminOnServerSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendAddAdminOnServerSignal, topBarController_, &TopBarController::handOverResponseAddAdminOnServerSignal);
        connect(serverConnector_, &ServerConnector::sendRemoveAdminOnServerSignal, topBarController_, &TopBarController::handOverResponseRemoveAdminOnServerSignal);
        connect(topBarController_, &TopBarController::accessToServerDeniedSignal, serverTableController_, &ServerTableController::slotDeleteServer);
        connect(&SelectedServerManager::instance(), &SelectedServerManager::serverRoleChangedSignal, topBarController_, &TopBarController::slotSetNewServerRole);
    }
}

void MainController::createChatsBarController()
{
    if(!chatsBarController_)
    {
        if(!serverTableController_)
        {
            createServerTableController();
        }

        chatsBarController_ = new ChatsBarController(this);
        connect(chatsBarController_, &ChatsBarController::getChatsSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendChatsSignal, chatsBarController_, &ChatsBarController::slotChatsProcessing);
        connect(chatsBarController_, &ChatsBarController::createChatSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendChatCreatedSignal, chatsBarController_, &ChatsBarController::slotChatCreatedProcessing);
        connect(serverConnector_, &ServerConnector::sendUserAddInChatSignal, chatsBarController_, &ChatsBarController::slotAddUserInChatProcessing);
        connect(serverTableController_, &ServerTableController::selectedServerDeletedSignal, chatsBarController_, &ChatsBarController::slotClearChat);
        connect(serverTableController_, &ServerTableController::serverSelectedSignal, chatsBarController_, &ChatsBarController::slotGetChats);
        connect(serverConnector_, &ServerConnector::sendSetNewMessage, chatsBarController_, &ChatsBarController::slotSetNewLastMessage);
        connect(serverConnector_, &ServerConnector::sendIncreaseMessageCounter, chatsBarController_, &ChatsBarController::slotIncreaseMessageCount);
        connect(serverConnector_, &ServerConnector::sendDecreaseMessageCounter, chatsBarController_, &ChatsBarController::slotDecreaseMessageCount);
    }
}

void MainController::createChatHistoryController()
{
    if(!chatHistoryController_)
    {
        chatHistoryController_ = new ChatHistoryController(this);
        connect(&SelectedChatManager::instance(), &SelectedChatManager::setNewChatIdSignal, chatHistoryController_, &ChatHistoryController::slotSetChatId);
        connect(chatHistoryController_, &ChatHistoryController::getChatDataSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendSetChatDataSignal, chatHistoryController_, &ChatHistoryController::slotSetChatData);
        connect(chatHistoryController_, &ChatHistoryController::sendMessageSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendSetNewMessage, chatHistoryController_, &ChatHistoryController::slotSetNewMessage);
        connect(chatHistoryController_, &ChatHistoryController::markMessageSignal, serverConnector_, &ServerConnector::slotSendToServer);
        connect(serverConnector_, &ServerConnector::sendMarkMessage, chatHistoryController_, &ChatHistoryController::slotMarkMessageProcessing);
    }
}

void MainController::createChatInfoBarController()
{
    if(!chatInfoBarController_)
    {
        chatInfoBarController_ = new ChatInfoBarController(this);
        connect(&SelectedChatManager::instance(), &SelectedChatManager::chatDataChangedSignal, chatInfoBarController_, &ChatInfoBarController::slotSetChatData);
        connect(&SelectedChatManager::instance(), &SelectedChatManager::chatAvatarChangedSignal, chatInfoBarController_, &ChatInfoBarController::slotSetChatAvatar);
        connect(&SelectedChatManager::instance(), &SelectedChatManager::clearChatDataSignal, chatInfoBarController_, &ChatInfoBarController::slotClearChatData);
        connect(&SelectedChatManager::instance(), &SelectedChatManager::setNewChatIdSignal, chatInfoBarController_, &ChatInfoBarController::slotChatIdChanged);
    }
}
