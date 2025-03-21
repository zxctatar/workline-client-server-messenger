#ifndef TOPBARCONTROLLER_H
#define TOPBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "UserAccountManager.h"
#include "ProfilePageController.h"
#include "ApplicationPageController.h"
#include "AddUserOnServerController.h"
#include "SelectedServerManager.h"

class TopBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(ApplicationPageController* applicationPageController READ getApplicationPageController NOTIFY applicationPageControllerChanged FINAL)
    Q_PROPERTY(ProfilePageController* profilePageController READ getProfilePageController NOTIFY profilePageControllerChanged FINAL)
    Q_PROPERTY(AddUserOnServerController* addUserController READ getAddUserController NOTIFY addUserControllerChanged FINAL)

public:
    explicit TopBarController(QObject* parent = nullptr);
    ~TopBarController();

    Q_INVOKABLE ProfilePageController* getProfilePageController();
    Q_INVOKABLE ApplicationPageController* getApplicationPageController();
    Q_INVOKABLE AddUserOnServerController* getAddUserController();
    Q_INVOKABLE void getUserRole() const;
    Q_INVOKABLE void deleteApplicationPageController();
    Q_INVOKABLE void deleteProfilePageController();
    Q_INVOKABLE void deleteAddUserOnServerController();
    Q_INVOKABLE void checkServerSelected();

signals:
    void profilePageControllerChanged();
    void applicationPageControllerChanged();
    void addUserControllerChanged();

    void setUserRoleSignal(const QString& userRole_) const;

    void handOverGetUnverUsersSignal(const QString& info_) const;
    void handOverReceivedUnverUsersSignal(const QJsonObject& jsonObj_) const;
    void handOverApproveUserSignal(const QString& info_) const;
    void handOverRejectUserSignal(const QString& info_) const;
    void handOverReceivedApproveUserSignal(const QJsonObject& jsonObj_) const;
    void handOverReceivedRejectUserSignal(const QJsonObject& jsonObj_) const;
    void handOverDeleteUnverUserSignal(const int userId_) const;

    void serverSelectedSignal();
    void selectedServerDeleted();

private:
    void createProfilePageController();
    void createApplicationPageController();
    void createAddUserOnServerController();

    std::shared_ptr<ProfilePageController> profilePageController_;
    std::shared_ptr<ApplicationPageController> applicationPageController_;
    std::shared_ptr<AddUserOnServerController> addUserController_;
};

#endif // TOPBARCONTROLLER_H
