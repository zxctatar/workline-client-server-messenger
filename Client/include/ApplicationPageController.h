#ifndef APPLICATIONPAGECONTROLLER_H
#define APPLICATIONPAGECONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "UnverifiedUserModel.h"
#include "JsonWorker.h"
#include "ImageWorker.h"

class ApplicationPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ApplicationPageController(QObject* parent = nullptr);
    ~ApplicationPageController();

    Q_INVOKABLE UnverifiedUserModel* getUnverUserModel() const;
    Q_INVOKABLE void getUnverUsers() const;
    Q_INVOKABLE void refreshUnverUsers();
    Q_INVOKABLE void approveUser(const int userId_);
    Q_INVOKABLE void rejectUser(const int userId_);
    Q_INVOKABLE void deleteUnverUserManager();

signals:
    void getUnverUsersSignal(const QString& info_) const;

    void approveUserSignal(const QString& info_);
    void rejectUserSignal(const QString& info_);

    void alreadyApprovedSignal() const;
    void alreadyRejectedSignal() const;
    void errorSignal() const;
    void approvedSignal() const;
    void rejectedSignal() const;

public slots:
    void slotUnverUsersProcessing(const QJsonObject& jsonObj_) const;
    void slotApproveUserProcessing(const QJsonObject& jsonObj_) const;
    void slotRejectUserProcessing(const QJsonObject& jsonObj_) const;
    void slotDeleteUnverUser(const int userId_) const;

private:
    std::shared_ptr<UnverifiedUserModel> unverUserModel_;
    JsonWorker jsonWorker_;
    ImageWorker imageWorker_;
};

#endif // APPLICATIONPAGECONTROLLER_H
