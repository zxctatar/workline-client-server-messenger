#include "../../include/ServerConnector.h"
#include <QJsonObject>
#include <arpa/inet.h>

ServerConnector::ServerConnector(const QString& strHost, const int port, QObject* parent)
    : QObject(parent)
    , nextBlockSize_(0)
    , strHost_(strHost)
    , port_(port)
    , socket_(new QTcpSocket())
{
    connectToServer();
    settingReconnectionTimer();
}

ServerConnector::~ServerConnector()
{
    socket_->deleteLater();
}

void ServerConnector::connectToServer()
{
    socket_->connectToHost(strHost_, port_);

    connect(socket_, &QTcpSocket::connected, this, &ServerConnector::slotConnected);
    connect(socket_, &QTcpSocket::readyRead, this, &ServerConnector::slotReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, &ServerConnector::slotError);
}

void ServerConnector::slotReadyRead()
{
    static uint32_t messageLength = 0;
    static QByteArray messageData;

    if (messageLength == 0 && socket_->bytesAvailable() >= sizeof(messageLength))
    {
        socket_->read(reinterpret_cast<char*>(&messageLength), sizeof(messageLength));
        messageLength = ntohl(messageLength);

        if (messageLength > 1024 * 1024) // Ограничение на размер сообщения (1 МБ)
        {
            qWarning() << "Message too large, closing connection";
            return;
        }
    }

    if (messageLength > 0)
    {
        while (socket_->bytesAvailable() > 0 && messageData.size() < messageLength)
        {
            messageData.append(socket_->readAll());
        }

        if (messageData.size() >= messageLength)
        {
            QByteArray jsonData = messageData.left(messageLength);
            QString str_ = QString::fromUtf8(jsonData);
            qDebug() << "Received JSON:" << str_;

            messageData.remove(0, messageLength);
            messageLength = 0;
        }
    }
}

void ServerConnector::slotConnected()
{
    qDebug() << "Connected to the server";
}

void ServerConnector::slotError(QAbstractSocket::SocketError err)
{
    QString strError_ =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                    "The host not found." :
                    err == QAbstractSocket::RemoteHostClosedError ?
                    "The remote host is closed." :
                    err == QAbstractSocket::ConnectionRefusedError ?
                    "The connection was refused." :
                    QString(socket_->errorString()));

    qDebug() << strError_;

    reconnectToServer();
}

void ServerConnector::settingReconnectionTimer()
{
    timerReconnect_.setInterval(5000);

    // Переподключение по таймеру
    connect(&timerReconnect_, &QTimer::timeout, this, [&] {
        if (socket_->state() == QAbstractSocket::UnconnectedState) {
            socket_->connectToHost(strHost_, port_);
        }
    });

    // Остановка таймера при успешном подключении
    connect(socket_, &QTcpSocket::connected, this, [&] {
        timerReconnect_.stop();
    });
}

void ServerConnector::reconnectToServer()
{
    qDebug() << "Trying to reconnect in 5 seconds...";

    if (!timerReconnect_.isActive()) {
        timerReconnect_.start();
    }
}





