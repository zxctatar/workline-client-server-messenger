#include "../../include/ServerConnector.h"
#include <QJsonObject>
#include <arpa/inet.h>

ServerConnector::ServerConnector(const QString& strHost, const int port, QObject* parent)
    : QObject(parent)
    , nextBlockSize_(0)
    , strHost_(strHost)
    , port_(port)
    , socket_(new QTcpSocket())
    , messageSize_(0)
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
    messageData_.append(socket_->readAll());

    while (true)
    {
        if (messageSize_ == 0)
        {
            if (messageData_.size() < sizeof(uint32_t))
                return;

            memcpy(&messageSize_, messageData_.constData(), sizeof(uint32_t));
            messageSize_ = ntohl(messageSize_);

            if (messageSize_ > 1024 * 1024)
            {
                messageData_.clear();
                messageSize_ = 0;
                return;
            }

            messageData_.remove(0, sizeof(uint32_t));
        }

        if (messageData_.size() < messageSize_)
            return;

        QByteArray jsonData_ = messageData_.left(messageSize_);
        messageData_.remove(0, messageSize_);
        messageSize_ = 0;

        QString str_ = QString::fromUtf8(jsonData_);
        workingWithResponse(jsonWorker_.JsonProcessing(str_));
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
        emit sendUserServersSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "DeleteServer")
    {
        emit sendDeleteServerIdSignal(jsonObj_["serverId"].toInt());
    }
    else if(jsonObj_["Info"] == "Get_UnverUsers")
    {
        emit sendUnverUsersSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Approve_User")
    {
        emit sendApproveUserSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Reject_User")
    {
        emit sendRejectUserSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Delete_unver_user")
    {
        emit sendDeleteUnverUserSignal(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["Info"] == "Get_Candidate_Users")
    {
        emit sendCandidateUsersSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Add_User_On_Server")
    {
        emit sendAddUserOnServerSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Delete_User_On_Server")
    {
        emit sendDeleteUserOnServerSignal(jsonObj_["userId"].toInt(), jsonObj_["serverId"].toInt());
    }
    else if(jsonObj_["Info"] == "Get_Chats")
    {
        emit sendChatsSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Create_Chat")
    {
        emit sendChatCreatedSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Get_Users_On_Server")
    {
        emit sendUsersOnServerSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Add_User_In_Chat")
    {
        emit sendUserAddInChatSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Add_New_Server")
    {
        emit sendAddNewServerSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Add_Admin_On_Server")
    {
        emit sendAddAdminOnServerSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Remove_Admin_On_Server")
    {
        emit sendRemoveAdminOnServerSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Get_Server_Role")
    {
        emit sendServerRoleSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Server_Role_Add")
    {
        emit sendServerRoleAddSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Server_Role_Removed")
    {
        emit sendServerRoleRemovedSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Get_Chat_Data")
    {
        emit sendSetChatDataSignal(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Set_New_Message")
    {
        emit sendSetNewMessage(jsonObj_);
    }
    else if(jsonObj_["Info"] == "Set_New_Message_Companion")
    {
        emit sendSetNewMessage(jsonObj_);
        emit sendIncreaseMessageCounter(jsonObj_["chatId"].toInt());
    }
    else if(jsonObj_["Info"] == "Mark_Message_For_User")
    {
        emit sendMarkMessage(jsonObj_);
        emit sendDecreaseMessageCounter(jsonObj_["chatId"].toInt());
    }
    else if(jsonObj_["Info"] == "Mark_Message_For_Companion")
    {
        emit sendMarkMessage(jsonObj_);
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

    if(UserAccountManager::instance().getAuthorized())
    {
        QString login_ = UserAccountManager::instance().getUserLogin();
        QString password_ = UserAccountManager::instance().getUserPassword();

        QString request_ = jsonWorker_.createJsonReconnect(login_, password_);

        slotSendToServer(request_);
    }
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





