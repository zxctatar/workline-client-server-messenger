#ifndef ADDUSERONSERVERCONTROLLER_H
#define ADDUSERONSERVERCONTROLLER_H

#include <QObject>
#include <qqml.h>
#include <memory>
#include "CandidateUserModel.h"

class AddUserOnServerController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AddUserOnServerController(QObject* parent = nullptr);
    ~AddUserOnServerController();

    Q_INVOKABLE CandidateUserModel* getCandidateUserModel();

private:
    std::shared_ptr<CandidateUserModel> candidateUserModel_;
};

#endif // ADDUSERONSERVERCONTROLLER_H
