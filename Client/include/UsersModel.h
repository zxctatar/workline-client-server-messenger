#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>
#include "SelectedServerManager.h"

class UsersModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UsersModel(QObject* parent = nullptr);
    ~UsersModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addUser(const int serverId_, const int userId_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const bool isServerAdmin_, const bool isGlobalAdmin_);
    void addAdminRole(const int userId_, const int serverId_);
    void removeAdminRole(const int userId_, const int serverId_);
    void clearUsers();

private:
    struct User
    {
        QString displayName_;
        int userId_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        bool isServerAdmin_;
    };

    QVector<User> users_;
};

#endif // USERSMODEL_H
