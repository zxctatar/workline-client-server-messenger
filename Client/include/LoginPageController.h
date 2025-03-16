#ifndef LOGINPAGECONTROLLER_H
#define LOGINPAGECONTROLLER_H

#include <QObject>
#include "qqml.h"
#include "ServerConnector.h"
#include "JsonWorker.h"

class LoginPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit LoginPageController(QObject* parent = nullptr);
    ~LoginPageController();

    Q_INVOKABLE void prepareLoginRequest(const QString& q_login, const QString& q_password) const;

signals:
    void loginRequestSignal(const QString& request_) const;

    void incorrectDataSignal() const;
    void accessAllowedSignal() const;
    void accessDeniedSignal() const;
    void errorLoginSignal() const;

    void sendUserDataSignal(const QString& receivedUserFirstName_, const QString& receivedUserLastName_, const QString& receivedUserMiddleName_, const QString& receivedUserEmail_, const QString& receivedUserPhoneNumber_, const QString& receivedUserLogin_, const QString& receivedUserPassword_, const int receivedUserId_, const QString& receivedUserRole_) const;

public slots:
    void slotResponseProcessing(const QJsonObject& jsonObj_) const;

private:
    JsonWorker jsonWorker_;
};

#endif // LOGINPAGECONTROLLER_H
