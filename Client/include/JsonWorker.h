#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class JsonWorker
{
public:
    explicit JsonWorker();
    ~JsonWorker();

    QJsonObject JsonProcessing(const QString& jsonStr_);

    QString createJsonGET_ID() const;
    QString createJsonRegistration(const QString& lastname_, const QString& firstname_, const QString& middlename_, const QString& login_, const QString& phoneNumber_, const QString& email_, const QString& password_) const;
    QString createJsonLogin(const QString& login_, const QString& password_) const;
    QString createJsonAddServer(const QString& serverName_, const QString& serverDescriptrion_) const;
    QString createJsonGetServers() const;
    QString createJsonReconnect(const QString& login_, const QString& password_) const;
    QString createJsonDeleteServer(const int serverId_) const;
    QString createJsonGetUnverUsers() const;
    QString createJsonApproveUser(const int userId_) const;
    QString createJsonRejectUser(const int userId_) const;

private:
};

#endif // JSONWORKER_H
