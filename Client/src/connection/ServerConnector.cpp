#include "../../include/ServerConnector.h"
#include <QJsonObject>


ServerConnector::ServerConnector(const QString& strHost, const int port, QObject* parent)
    : QObject(parent)
    , nextBlockSize_(0)
    , strHost_(strHost)
    , port_(port)
    , socket_(new QTcpSocket())
{
    settingReconnectionTimer();
    connectToServer();
}

ServerConnector::~ServerConnector()
{
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
    QDataStream in(socket_);
    for(;;)
    {
        if(!nextBlockSize_)
        {
            if(socket_->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> nextBlockSize_;
        }

        if(socket_->bytesAvailable() < nextBlockSize_)
        {
            break;
        }

        QString str_;
        in >> str_;

        QJsonObject jsonObject_ = jsonWorker_.JsonProcessing(str_);

        nextBlockSize_ = 0;
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
        qDebug() << "Reconnected";
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





