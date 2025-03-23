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

signals:
    void getCandidateUsersSignal(const QString& info_) const;

public slots:
    void slotCandidateUsersProcessing(const QJsonObject& jsonObj_) const;

private:
    JsonWorker jsonWorker_;

    std::shared_ptr<CandidateUserModel> candidateUserModel_;
};

#endif // ADDUSERONSERVERCONTROLLER_H
