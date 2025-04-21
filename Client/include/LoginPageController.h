#ifndef LOGINPAGECONTROLLER_H
#define LOGINPAGECONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"
#include "ImageWorker.h"
#include "UserAccountManager.h"
#include "ChatsManager.h"

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

public slots:
    void slotResponseProcessing(const QJsonObject& jsonObj_) const;

private:
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
};

#endif // LOGINPAGECONTROLLER_H
