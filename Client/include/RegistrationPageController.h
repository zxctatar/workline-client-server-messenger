#ifndef RegistrationPAGECONTROLLER_H
#define RegistrationPAGECONTROLLER_H

#include <QObject>
#include "qqml.h"
#include "ServerConnector.h"
#include "ImageWorker.h"
#include "JsonWorker.h"

class RegistrationPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegistrationPageController(QObject* parent = nullptr);
    ~RegistrationPageController();

    Q_INVOKABLE void prepareRegistrationRequest(const QString& q_image, const QString& q_lastName, const QString& q_firstName, const QString& q_middleName, const QString& q_birthDate, const QString& q_login, const QString& q_phoneNumber, const QString& q_email, const QString& q_password) const;

signals:
    void registrationRequestSignal(const QString& request_) const;

    void loginExistsSignal() const;
    void phoneNumberExistsSignal() const;
    void emailExistsSignal() const;
    void regOkSignal() const;
    void errorRegSignal() const;

public slots:
    void slotCodeProcessing(const QString& code_) const;

private:
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
};

#endif // RegistrationPAGECONTROLLER_H
