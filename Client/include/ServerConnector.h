#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QTcpSocket>
#include "JsonWorker.h"
#include "UserAccountManager.h"
#include <QTimer>

class ServerConnector : public QObject
{
    Q_OBJECT

public:
    explicit ServerConnector(const QString& strHost, const int port, QObject* parent = nullptr);
    ~ServerConnector();

private slots:
    void slotReadyRead();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError);

public slots:
    void slotSendToServer(const QString& info_);

signals:
    void sendRegistrationCodeSignal(const QString& code_);
    void sendLoginCodeSignal(const QJsonObject& jsonObj_);
    void sendServerTableCodeSignal(const QJsonObject& jsonObj_);
    void sendUserServersSignal(const QJsonObject& jsonObj_);
    void sendDeleteServerIdSignal(const int serverId_);
    void sendUnverUsersSignal(const QJsonObject& jsonObj_);
    void sendApproveUserSignal(const QJsonObject& jsonObj_);
    void sendRejectUserSignal(const QJsonObject& jsonObj_);
    void sendDeleteUnverUserSignal(const int userId_);
    void sendCandidateUsersSignal(const QJsonObject& jsonObj_);
    void sendAddUserOnServerSignal(const QJsonObject& jsonObj_);
    void sendDeleteUserOnServerSignal(const int userId_, const int serverId_);
    void sendChatsSignal(const QJsonObject& jsonObj_);
    void sendChatCreatedSignal(const QJsonObject& jsonObj_);
    void sendUsersOnServerForConfigureAdminSignal(const QJsonObject& jsonObj_);
    void sendUsersOnServerForAddUserInChatSignal(const QJsonObject& jsonObj_);
    void sendUserAddInChatSignal(const QJsonObject& jsonObj_);
    void sendAddNewServerSignal(const QJsonObject& jsonObj_);
    void sendAddAdminOnServerSignal(const QJsonObject& jsonObj_);
    void sendRemoveAdminOnServerSignal(const QJsonObject& jsonObj_);
    void sendServerRoleSignal(const QJsonObject& jsonObj_);
    void sendServerRoleAddSignal(const QJsonObject& jsonObj_);
    void sendServerRoleRemovedSignal(const QJsonObject& jsonObj_);
    void sendSetChatDataSignal(const QJsonObject& jsonObj_);
    void sendSetNewMessageSignal(const QJsonObject& jsonObj_);
    void sendMarkMessageSignal(const QJsonObject& jsonObj_);
    void sendIncreaseMessageCounterSignal(const int chatId_, const bool isGroup_);
    void sendDecreaseMessageCounterSignal(const int chatId_, const bool isGroup_);
    void sendCodeCreateNewGroupChatSignal(const QString& code_);
    void sendCreateNewGroupChatSignal(const QJsonObject& jsonObj_);

private:
    void connectToServer();
    void reconnectToServer();
    void settingReconnectionTimer();
    void workingWithResponse(const QJsonObject& jsonObj_);

    quint16 nextBlockSize_;
    const QString strHost_;
    const int port_;
    QTcpSocket* socket_;    
    JsonWorker jsonWorker_;
    QTimer timerReconnect_;
    uint32_t messageSize_;
    QByteArray messageData_;
};

#endif // SERVERCONNECTOR_H
