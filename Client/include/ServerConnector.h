#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QTcpSocket>
#include "JsonWorker.h"
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
    void sendUserServers(const QJsonObject& jsonObj_);
    void checkAuthorizationSignal();


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
};

#endif // SERVERCONNECTOR_H
