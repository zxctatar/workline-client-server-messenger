#ifndef PROFILEPAGECONTROLLER_H
#define PROFILEPAGECONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "UserAccountManager.h"

class ProfilePageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ProfilePageController(QObject* parent = nullptr);
    ~ProfilePageController();

    Q_INVOKABLE void getUserData() const;

signals:
    void setUserDataSignal(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const;
};

#endif // PROFILEPAGECONTROLLER_H
