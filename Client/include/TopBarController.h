#ifndef TOPBARCONTROLLER_H
#define TOPBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <ApplicationPageController.h>

class TopBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(ApplicationPageController* applicationPageController READ getApplicationPageController NOTIFY applicationPageControllerChanged FINAL)

public:
    explicit TopBarController(QObject* parent = nullptr);
    ~TopBarController();

    Q_INVOKABLE void getUserRole() const;
    Q_INVOKABLE void getUserData() const;
    Q_INVOKABLE ApplicationPageController* getApplicationPageController();

signals:
    void applicationPageControllerChanged();
    void needUserRoleSignal() const;
    void needUserDataSignal() const;
    void setUserRoleSignal(const QString& userRole_) const;
    void setUserDataSignal(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const;

    void handOverGetUnverUsersSignal(const QString& info_) const;
    void handOverReceivedUnverUsersSignal(const QJsonObject& jsonObj_) const;
    void handOverApproveUserSignal(const QString& info_) const;
    void handOverRejectUserSignal(const QString& info_) const;
    void handOverReceivedApproveUserSignal(const QJsonObject& jsonObj_) const;
    void handOverReceivedRejectUserSignal(const QJsonObject& jsonObj_) const;
    void handOverDeleteUnverUserSignal(const int userId_) const;

public slots:
    void slotSetUserRole(const QString& userRole_) const;
    void slotSetUserData(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const;

private:
    void createApplicationPageController();

    ApplicationPageController* applicationPageController_;
};

#endif // TOPBARCONTROLLER_H
