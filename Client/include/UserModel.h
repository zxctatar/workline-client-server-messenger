#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"

class UserModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UserModel(QObject* parent = nullptr);
    ~UserModel();

    void setUserData(const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_);
    QString getUserRole() const;
    bool getAuthorized() const;
    QString getUserLogin() const;
    QString getUserPassword() const;
    QString getUserFirstName() const;
    QString getUserLastName() const;
    QString getUserMiddleName() const;
    QString getUserEmail() const;
    QString getUserPhoneNumber() const;

private:
    int id_;
    QString userRole_;    
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

#endif // USERMODEL_H
