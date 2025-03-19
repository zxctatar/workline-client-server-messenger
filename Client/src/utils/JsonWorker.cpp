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

QString JsonWorker::createJsonGET_ID() const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "GET_ID");
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}

QString JsonWorker::createJsonRegistration(const QString& lastname_, const QString& firstname_, const QString& middlename_, const QString& login_, const QString& phoneNumber_, const QString& email_, const QString& password_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Registration");
    jsonObject_.insert("lastname", QJsonValue::fromVariant(lastname_));
    jsonObject_.insert("firstname", QJsonValue::fromVariant(firstname_));
    jsonObject_.insert("middlename", QJsonValue::fromVariant(middlename_));
    jsonObject_.insert("login", QJsonValue::fromVariant(login_));
    jsonObject_.insert("phonenumber", QJsonValue::fromVariant(phoneNumber_));
    jsonObject_.insert("email", QJsonValue::fromVariant(email_));
    jsonObject_.insert("password", QJsonValue::fromVariant(password_));
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

QString JsonWorker::createJsonAddServer(const QString& serverName_, const QString& serverDescriptrion_) const
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", "Add_Server");
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


