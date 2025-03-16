#ifndef USERACCOUNTCONTROLLER_H
#define USERACCOUNTCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "UserModel.h"
#include "JsonWorker.h"

class UserAccountController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UserAccountController(QObject* parent = nullptr);
    ~UserAccountController();

signals:
    void sendUserRoleSignal(const QString& userRole_) const;
    void sendUserDataSignal(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail, const QString& userPhoneNumber_);
    void sendAuthorizationDataSignal(const QString& request_) const;

public slots:
    void slotSetUserData(const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_);
    void slotSendUserData();
    void slotSendUserRole();
    void slotCheckAuthorization();

private:
    UserModel* userModel_;
    JsonWorker jsonWorker_;
};

#endif // USERACCOUNTCONTROLLER_H
