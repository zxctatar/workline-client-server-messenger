#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"

class UserModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UserModel(QObject* parent = nullptr);
    ~UserModel();

public slots:
    // void setIdSlot(const int received_id_);
    // void setUserRoleSlot(const std::string& userRole_);

    void slotSetUserData(const int receivedUserId_, const QString& receivedUserRole_);

    void slotSendUserRole() const;

signals:
    void sendUserRoleSignal(const QString& userRole_) const;

private:
    int id_;
    QString userRole_;
    JsonWorker jsonWorker_;
};

#endif // USERMODEL_H
