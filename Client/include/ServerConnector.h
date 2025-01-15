#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QTcpSocket>
#include "JsonWorker.h"

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

private:
    void connectToServer();
    void reconnectToServer();

    quint16 nextBlockSize_;
    const QString strHost_;
    const int port_;
    QTcpSocket* socket_;    
    JsonWorker jsonWorker_;
};

#endif // SERVERCONNECTOR_H
