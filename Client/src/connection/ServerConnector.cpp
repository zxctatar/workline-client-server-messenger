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

    socket_->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    connect(socket_, &QTcpSocket::connected, this, &ServerConnector::slotConnected);
    connect(socket_, &QTcpSocket::readyRead, this, &ServerConnector::slotReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, &ServerConnector::slotError);
}

void ServerConnector::slotReadyRead()
{
    static uint32_t message_size_ = 0;
    static QByteArray messageData_;

    if (message_size_ == 0 && socket_->bytesAvailable() >= sizeof(message_size_))
    {
        socket_->read(reinterpret_cast<char*>(&message_size_), sizeof(message_size_));
        message_size_ = ntohl(message_size_);

        if (message_size_ > 1024 * 1024) // Ограничение на размер сообщения (1 МБ)
        {
            qWarning() << "Message too large, closing connection";
            return;
        }
    }

    if (message_size_ > 0)
    {
        while (socket_->bytesAvailable() > 0 && messageData_.size() < message_size_)
        {
            QByteArray chunk_ = socket_->read(message_size_ - messageData_.size());
            messageData_.append(chunk_);
        }

        if (messageData_.size() >= message_size_)
        {
            QByteArray jsonData = messageData_.left(message_size_);
            QString str_ = QString::fromUtf8(jsonData);

            messageData_.remove(0, message_size_);
            message_size_ = 0;

            workingWithResponse(jsonWorker_.JsonProcessing(str_));
        }
    }
}

void ServerConnector::workingWithResponse(const QJsonObject& jsonObj_)
{
    if(jsonObj_["Info"] == "Registration")
    {
        emit sendRegistrationCodeSignal(jsonObj_["Code"].toString());
    }
    else if(jsonObj_["Info"] == "Login")
    {
        emit sendLoginCodeSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Add_Server")
    {
        emit sendServerTableCodeSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Get_Servers")
    {
        emit sendUserServers(jsonObj_);
    }
    else if(jsonObj_["Info"] == "DeleteServer")
    {
        emit sendDeleteServerId(jsonObj_["serverId"].toInt());
    }
    else if(jsonObj_["Info"] == "Get_UnverUsers")
    {
        emit sendUnverUsers(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Approve_User")
    {
        emit sendApproveUser(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Reject_User")
    {
        emit sendRejectUser(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Delete_unver_user")
    {
        emit sendDeleteUnverUser(jsonObj_["userId"].toInt());
    }
}

void ServerConnector::slotSendToServer(const QString& request_)
{
    QByteArray data_ = request_.toUtf8();

    uint32_t lenght_ = htonl(data_.size());

    if(socket_->state() == QAbstractSocket::ConnectedState)
    {
        socket_->write(reinterpret_cast<char*>(&lenght_), sizeof(lenght_));
        socket_->write(data_);

        qDebug() << "Отправлено";
    }
}


void ServerConnector::slotConnected()
{
    qDebug() << "Connected to the server";

    emit checkAuthorizationSignal();
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





