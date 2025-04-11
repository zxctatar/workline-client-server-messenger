#include "../../../include/UsersModel.h"
#include <algorithm>

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
    case Qt::UserRole + 1:
        return user_.userId_;
    case Qt::UserRole + 2:
        return user_.isServerAdmin_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::UserRole + 1] = "id";
    roles[Qt::UserRole + 2] = "isServerAdmin";
    return roles;
}

void UsersModel::addUser(const int serverId_, const int userId_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const bool isServerAdmin_, const bool isGlobalAdmin_)
{
    if(SelectedServerManager::instance().getServerId() == serverId_ && !isGlobalAdmin_)
    {
        QString displayName_ = lastName_ + ' ' + firstName_[0] + ". " + middleName_[0] + '.';

        beginInsertRows(QModelIndex(), users_.size(), users_.size());
        users_.append({displayName_, userId_, firstName_, lastName_, middleName_, isServerAdmin_});
        endInsertRows();
    }
}

void UsersModel::addAdminRole(const int userId_, const int serverId_)
{
    int currentServerId_ = SelectedServerManager::instance().getServerId();

    if(currentServerId_ == serverId_)
    {
        auto it_ = std::find_if(users_.begin(), users_.end(), [userId_](const User& user_){
            return userId_ == user_.userId_;
        });

        if(it_ != users_.end())
        {
            int row = std::distance(users_.begin(), it_);

            it_->isServerAdmin_ = true;

            QVector<int> roles_;
            roles_ << Qt::UserRole + 2;

            emit dataChanged(index(row), index(row), roles_);
        }
    }
}

void UsersModel::removeAdminRole(const int userId_, const int serverId_)
{
    int currentServerId_ = SelectedServerManager::instance().getServerId();

    if(currentServerId_ == serverId_)
    {
        auto it_ = std::find_if(users_.begin(), users_.end(), [userId_](const User& user_){
            return userId_ == user_.userId_;
        });

        if(it_ != users_.end())
        {
            int row = std::distance(users_.begin(), it_);

            it_->isServerAdmin_ = false;

            QVector<int> roles_;
            roles_ << Qt::UserRole + 2;

            emit dataChanged(index(row), index(row), roles_);
        }
    }
}

void UsersModel::clearUsers()
{
    beginRemoveRows(QModelIndex(), 0, users_.size() - 1);
    users_.clear();
    endRemoveRows();
}
