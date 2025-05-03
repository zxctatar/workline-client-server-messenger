#ifndef TOPBARCONTROLLER_H
#define TOPBARCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "UserAccountManager.h"
#include "SelectedServerManager.h"
#include "ProfilePageController.h"
#include "ApplicationPageController.h"
#include "AddUserOnServerController.h"
#include "ConfigureAdminController.h"
#include "CreateGroupChatController.h"

class TopBarController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(ApplicationPageController* applicationPageController READ getApplicationPageController NOTIFY applicationPageControllerChanged FINAL)
    Q_PROPERTY(ProfilePageController* profilePageController READ getProfilePageController NOTIFY profilePageControllerChanged FINAL)
    Q_PROPERTY(AddUserOnServerController* addUserController READ getAddUserController NOTIFY addUserControllerChanged FINAL)
    Q_PROPERTY(ConfigureAdminController* configureAdminController READ getConfigureAdminController NOTIFY configureAdminControllerChanged FINAL)
    Q_PROPERTY(CreateGroupChatController* createGroupChatController READ getCreateGroupChatController NOTIFY createGroupChatControllerChanged FINAL)

public:
    explicit TopBarController(QObject* parent = nullptr);
    ~TopBarController();

    Q_INVOKABLE ProfilePageController* getProfilePageController();
    Q_INVOKABLE ApplicationPageController* getApplicationPageController();
    Q_INVOKABLE AddUserOnServerController* getAddUserController();
    Q_INVOKABLE ConfigureAdminController* getConfigureAdminController();
    Q_INVOKABLE CreateGroupChatController* getCreateGroupChatController();
    Q_INVOKABLE void getUserRole() const;
    Q_INVOKABLE void deleteApplicationPageController();
    Q_INVOKABLE void deleteProfilePageController();
    Q_INVOKABLE void deleteAddUserOnServerController();
    Q_INVOKABLE void deleteConfigureAdminController();
    Q_INVOKABLE void deleteCreateGroupChatController();
    Q_INVOKABLE void checkServerSelected();
    Q_INVOKABLE void accessToServerDenied(const int serverId_);
    Q_INVOKABLE void getServerId();
    Q_INVOKABLE void getServerRole();

signals:
    void profilePageControllerChanged();
    void applicationPageControllerChanged();
    void addUserControllerChanged();
    void configureAdminControllerChanged();
    void createGroupChatControllerChanged();

    void setServerId(const int serverId_) const;
    void setUserRoleSignal(const QString& userRole_) const;
    void setServerRoleSignal(const int serverRole_) const;

    void handOverGetUnverUsersSignal(const QString& info_) const;
    void handOverReceivedUnverUsersSignal(const QJsonObject& jsonObj_) const;
    void handOverApproveUserSignal(const QString& info_) const;
    void handOverRejectUserSignal(const QString& info_) const;
    void handOverReceivedApproveUserSignal(const QJsonObject& jsonObj_) const;
    void handOverReceivedRejectUserSignal(const QJsonObject& jsonObj_) const;
    void handOverDeleteUnverUserSignal(const int userId_) const;
    void handOverGetCandidateUsersSignal(const QString& info_) const;
    void handOverReceivedCandidateUsersSignal(const QJsonObject& jsonObj_) const;
    void handOverRequestAddUserSignal(const QString& info_) const;
    void handOverAddUserOnServerSignal(const QJsonObject& jsonObj_) const;
    void handOverDeleteUserOnServerSignal(const int userId_, const int serverId_) const;
    void handOverGetUsersOnServerSignal(const QString& info_);
    void handOverSendUsersOnServerForConfigureAdminSignal(const QJsonObject& jsonObj_);
    void handOverSendUsersOnServerForAddUserInChatSignal(const QJsonObject& jsonObj_);
    void handOverAddAdminOnServerSignal(const QString& info_);
    void handOverRemoveAdminOnServerSignal(const QString& info_);
    void handOverResponseAddAdminOnServerSignal(const QJsonObject& jsonObj_);
    void handOverResponseRemoveAdminOnServerSignal(const QJsonObject& jsonObj_);
    void handOverCreateGroupChatSignal(const QString& info_);
    void handOverCodeCreateGroupChatSignal(const QString& code_);

    void serverSelectedSignal();
    void selectedServerDeletedSignal();
    void accessToServerDeniedSignal(const int serverId_);

public slots:
    void slotSetNewServerRole();

private:
    void createProfilePageController();
    void createApplicationPageController();
    void createAddUserOnServerController();
    void createConfigureAdminController();
    void createCreateGroupChatController();

    std::shared_ptr<ProfilePageController> profilePageController_;
    std::shared_ptr<ApplicationPageController> applicationPageController_;
    std::shared_ptr<AddUserOnServerController> addUserController_;
    std::shared_ptr<ConfigureAdminController> configureAdminController_;
    std::shared_ptr<CreateGroupChatController> createGroupChatController_;
};

#endif // TOPBARCONTROLLER_H
