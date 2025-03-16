#ifndef TOPBARCONTROLLER_H
#define TOPBARCONTROLLER_H

#include <QObject>
#include <qqml.h>

class TopBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TopBarController(QObject* parent = nullptr);
    ~TopBarController();

    Q_INVOKABLE void getUserRole() const;
    Q_INVOKABLE void getUserData() const;

signals:
    void needUserRoleSignal() const;
    void needUserDataSignal() const;
    void setUserRoleSignal(const QString& userRole_) const;
    void setUserDataSignal(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const;

public slots:
    void slotSetUserRole(const QString& userRole_) const;
    void slotSetUserData(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const;

private:

};

#endif // TOPBARCONTROLLER_H
