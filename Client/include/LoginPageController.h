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
    explicit LoginPageController(ServerConnector& serverConnector_, QObject* parent = nullptr);
    ~LoginPageController();

    Q_INVOKABLE void prepareLoginRequest(const QString& q_login, const QString& q_password) const;

signals:
    void loginRequestSignal(const QString& request_) const;

    void incorrectDataSignal() const;
    void accessAllowedSignal() const;
    void accessDeniedSignal() const;
    void errorLoginSignal() const;

public slots:
    void codeProcessing(const QString& code_) const;

private:
    ServerConnector& serverConnector_;
    JsonWorker jsonWorker_;
};

#endif // LOGINPAGECONTROLLER_H
