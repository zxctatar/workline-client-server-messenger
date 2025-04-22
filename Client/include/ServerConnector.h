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
    void sendUsersOnServerSignal(const QJsonObject& jsonObj_);
    void sendUserAddInChatSignal(const QJsonObject& jsonObj_);
    void sendAddNewServerSignal(const QJsonObject& jsonObj_);
    void sendAddAdminOnServerSignal(const QJsonObject& jsonObj_);
    void sendRemoveAdminOnServerSignal(const QJsonObject& jsonObj_);
    void sendServerRoleSignal(const QJsonObject& jsonObj_);
    void sendServerRoleAddSignal(const QJsonObject& jsonObj_);
    void sendServerRoleRemovedSignal(const QJsonObject& jsonObj_);
    void sendSetChatDataSignal(const QJsonObject& jsonObj_);
    void sendSetNewMessage(const QJsonObject& jsonObj_);
    void sendMarkMessage(const QJsonObject& jsonObj_);
    void sendIncreaseMessageCounter(const int chatId_);
    void sendDecreaseMessageCounter(const int chatId_);

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
