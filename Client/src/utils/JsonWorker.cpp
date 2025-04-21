#include "../../include/JsonWorker.h"

JsonWorker::JsonWorker()
{
}

JsonWorker::~JsonWorker()
{
}

QJsonObject JsonWorker::JsonProcessing(const QString& jsonStr_)
{
    QJsonDocument jsonDoc_ = QJsonDocument::fromJson(jsonStr_.toUtf8());

    if(!jsonDoc_.isObject() || jsonDoc_.isNull())
    {
        qWarning() << "Invalid JSON";
        return QJsonObject();
    }

    return jsonDoc_.object();
}

QString JsonWorker::createJsonGetUserId() const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "GET_ID");
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonRegistration(const QString& image_, const QString& lastname_, const QString& firstname_, const QString& middlename_, const QString& birthDate_, const QString& login_, const QString& phoneNumber_, const QString& email_, const QString& password_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Registration");
    jsonObject_.insert("image", image_);
    jsonObject_.insert("lastname", lastname_);
    jsonObject_.insert("firstname", firstname_);
    jsonObject_.insert("middlename", middlename_);
    jsonObject_.insert("birthDate", birthDate_);
    jsonObject_.insert("login", login_);
    jsonObject_.insert("phonenumber", phoneNumber_);
    jsonObject_.insert("email", email_);
    jsonObject_.insert("password", password_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonLogin(const QString& login_, const QString& password_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Login");
    jsonObject_.insert("login", login_);
    jsonObject_.insert("password", password_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonAddServer(const QString& image_, const QString& serverName_, const QString& serverDescriptrion_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Add_Server");
    jsonObject_.insert("image", image_);
    jsonObject_.insert("serverName", serverName_);
    jsonObject_.insert("serverDescription", serverDescriptrion_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetServers() const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Servers");
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonReconnect(const QString& login_, const QString& password_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Reconnect");
    jsonObject_.insert("login", login_);
    jsonObject_.insert("password", password_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonDeleteServer(const int serverId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "DeleteServer");
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetUnverUsers() const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_UnverUsers");
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonApproveUser(const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Approve_User");
    jsonObject_.insert("userId", userId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonRejectUser(const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Reject_User");
    jsonObject_.insert("userId", userId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetCandidateUsers(const int serverId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Candidate_Users");
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonAddUserOnServer(const int userId_, const int serverId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Add_User_On_Server");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetChats(const int serverId_, const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Chats");
    jsonObject_.insert("serverId", serverId_);
    jsonObject_.insert("userId", userId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonCreateChat(const int serverId_, const int userId_, const int companionId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Create_Chat");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("companionId", companionId_);
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetUsersOnServer(const int serverId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Users_On_Server");
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonAddAdminOnServer(const int serverId_, const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Add_Admin_On_Server");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonRemoveAdminOnServer(const int serverId_, const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Remove_Admin_On_Server");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetServerRole(const int userId_, const int serverId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Server_Role");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonGetChatHistory(const int chatId_, const int serverId_, const int userId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Get_Chat_Data");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    jsonObject_.insert("chatId", chatId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonSendMessage(const int chatId_, const int userId_, const int serverId_, const QString& message_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Send_Message");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("serverId", serverId_);
    jsonObject_.insert("chatId", chatId_);
    jsonObject_.insert("message", message_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonMarkMessageAsRead(const int messageId_, const int userId_, const int chatId_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Mark_Message");
    jsonObject_.insert("userId", userId_);
    jsonObject_.insert("chatId", chatId_);
    jsonObject_.insert("messageId", messageId_);
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}
