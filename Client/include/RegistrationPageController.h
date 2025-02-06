#ifndef REGISTRATIONPAGECONTROLLER_H
#define REGISTRATIONPAGECONTROLLER_H

#include <QObject>
#include "qqml.h"
#include "ServerConnector.h"
#include "JsonWorker.h"

class RegistrationPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegistrationPageController(ServerConnector& serverConnector_, QObject* parent = nullptr);
    ~RegistrationPageController();

    Q_INVOKABLE void prepareRegistrationRequest(const QString& q_initials, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& password) const;

    Q_INVOKABLE void emitSignal();
signals:
    void mySignal();

private:
    ServerConnector& serverConnector_;
    JsonWorker jsonWorker_;
};

#endif // REGISTRATIONPAGECONTROLLER_H
