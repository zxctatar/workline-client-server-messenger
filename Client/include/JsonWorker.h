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

    QString createJsonGetUserId() const;
    QString createJsonRegistration(const QString& image_, const QString& lastname_, const QString& firstname_, const QString& middlename_, const QString& birthDate_, const QString& login_, const QString& phoneNumber_, const QString& email_, const QString& password_) const;
    QString createJsonLogin(const QString& login_, const QString& password_) const;
    QString createJsonAddServer(const QString& image_, const QString& serverName_, const QString& serverDescriptrion_) const;
    QString createJsonGetServers() const;
    QString createJsonReconnect(const QString& login_, const QString& password_) const;
    QString createJsonDeleteServer(const int serverId_) const;
    QString createJsonGetUnverUsers() const;
    QString createJsonApproveUser(const int userId_) const;
    QString createJsonRejectUser(const int userId_) const;
    QString createJsonGetCandidateUsers(const int serverId_) const;
    QString createJsonAddUserOnServer(const int userId_, const int serverId_) const;
    QString createJsonGetChats(const int serverId_, const int userId_) const;
    QString createJsonCreateChat(const int serverId_, const int userId_, const int companionId_) const;
    QString createJsonGetUsersOnServer(const int serverId_) const;
    QString createJsonAddAdminOnServer(const int serverId_, const int userId_) const;
    QString createJsonRemoveAdminOnServer(const int serverId_, const int userId_) const;
    QString createJsonGetServerRole(const int userId_, const int serverId_) const;
    QString createJsonGetChatHistory(const int chatId_, const int serverId_, const int userId_) const;
    QString createJsonSendMessage(const int chatId_, const int userId_, const int serverId_, const QString& message_) const;

private:
};

#endif // JSONWORKER_H
