#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include "JsonWorker.h"

class UserAccountManager : public QObject
{
    Q_OBJECT

public:
    static UserAccountManager& instance();

    void setUserData(const QString& receivedUserAvatar_, const QString& receivedBirthDate_, const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_);
    QString getUserRole() const;
    bool getAuthorized() const;
    QString getUserAvatarPath() const;
    QString getUserBirthDate() const;
    QString getUserLogin() const;
    QString getUserPassword() const;
    QString getUserFirstName() const;
    QString getUserLastName() const;
    QString getUserMiddleName() const;
    QString getUserEmail() const;
    QString getUserPhoneNumber() const;
    int getUserId() const;

private:
    explicit UserAccountManager(QObject* parent = nullptr);
    ~UserAccountManager();

    int id_;
    QString userRole_;
    QString userAvatarPath_;
    QString userBirthDate_;
    QString userLogin_;
    QString userPassword_;
    QString userFirstName_;
    QString userLastName_;
    QString userMiddleName_;
    QString userEmail_;
    QString userPhoneNumber_;
    bool isAuthorized;

    JsonWorker jsonWorker_;
};

#endif // USERMANAGER_H
