#ifndef ADDUSERONSERVERCONTROLLER_H
#define ADDUSERONSERVERCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "CandidateUserModel.h"
#include "SelectedServerManager.h"
#include "JsonWorker.h"

class AddUserOnServerController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AddUserOnServerController(QObject* parent = nullptr);
    ~AddUserOnServerController();

    Q_INVOKABLE CandidateUserModel* getCandidateUserModel();
    Q_INVOKABLE void getCandidateUsers() const;
    Q_INVOKABLE void refreshCandidateUsers() const;
    Q_INVOKABLE void requestAddUser(const int userId_, const int serverId_) const;
    Q_INVOKABLE void getServerId() const;

signals:
    void getCandidateUsersSignal(const QString& info_) const;
    void requestAddUserSignal(const QString& info_) const;
    void setServerIdSignal(const int serverId_) const;

    void userNotVerifiedSignal() const;
    void userAlreadyAddedSignal() const;
    void userAddedOnServerSignal() const;
    void errorSignal() const;

public slots:
    void slotCandidateUsersProcessing(const QJsonObject& jsonObj_) const;
    void slotAddUserOnServerProccessing(const QJsonObject& jsonObj_) const;
    void slotDeleteUserOnServer(const int userId_, const int serverId_) const;

private:
    JsonWorker jsonWorker_;

    std::shared_ptr<CandidateUserModel> candidateUserModel_;
};

#endif // ADDUSERONSERVERCONTROLLER_H
