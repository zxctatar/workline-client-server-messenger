#ifndef RegistrationPAGECONTROLLER_H
#define RegistrationPAGECONTROLLER_H

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

    Q_INVOKABLE void prepareRegistrationRequest(const QString& q_initials, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& q_password) const;

signals:
    void registrationRequestSignal(const QString& request_) const;

    void loginExistsSignal() const;
    void phoneNumberExistsSignal() const;
    void emailExistsSignal() const;
    void regOkSignal() const;
    void errorRegSignal() const;

public slots:
    void codeProcessing(const QString& code_) const;

private:
    ServerConnector& serverConnector_;
    JsonWorker jsonWorker_;
};

#endif // RegistrationPAGECONTROLLER_H
