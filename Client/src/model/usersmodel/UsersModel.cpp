#include "../../../include/UsersModel.h"

UsersModel::UsersModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

UsersModel::~UsersModel()
{
}

int UsersModel::rowCount(const QModelIndex& parent_) const
{
    Q_UNUSED(parent_);
    return users_.size();
}

QVariant UsersModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= users_.size())
    {
        return QVariant();
    }

    const User& user_ = users_.at(index_.row());

    switch(role_)
    {
    case Qt::DisplayRole:
        return user_.displayName_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "displayName";
    return roles;
}

void UsersModel::addUser(const int serverId_, const int userId_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const bool isServerAdmin_, const bool isGlobalAdmin_)
{
    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        QString displayName_ = lastName_ + ' ' + firstName_[0] + ". " + middleName_[0] + '.';

        beginInsertRows(QModelIndex(), users_.size(), users_.size());
        users_.append({displayName_, userId_, firstName_, lastName_, middleName_, isServerAdmin_, isGlobalAdmin_});
        endInsertRows();
    }
}
