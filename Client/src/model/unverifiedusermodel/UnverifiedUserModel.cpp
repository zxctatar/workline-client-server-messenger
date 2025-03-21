#include "../../../include/UnverifiedUserModel.h"
#include <algorithm>

UnverifiedUserModel::UnverifiedUserModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

UnverifiedUserModel::~UnverifiedUserModel()
{
}

int UnverifiedUserModel::rowCount(const QModelIndex& parent_) const
{
    Q_UNUSED(parent_);
    return unverifiedUsers_.size();
}

QVariant UnverifiedUserModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= unverifiedUsers_.size())
    {
        return QVariant();
    }

    const UnverifiedUsers& user_ = unverifiedUsers_.at(index_.row());

    switch(role_)
    {
    case Qt::DisplayRole:
        return user_.displayName_;
    case Qt::UserRole + 1:
        return user_.id_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> UnverifiedUserModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::UserRole + 1] = "id";
    return roles;
}

void UnverifiedUserModel::addUnverifiedUser(const int id_, const QString& firstName_, const QString& lastName_, const QString& middleName_)
{
    if(containsUnverifiedUser(id_))
    {
        return;
    }

    QString displayName_ = lastName_ + ' ' + firstName_[0] + ". " + middleName_[0] + '.';

    beginInsertRows(QModelIndex(), unverifiedUsers_.size(), unverifiedUsers_.size());
    unverifiedUsers_.append({id_, firstName_, lastName_, middleName_, displayName_});
    endInsertRows();
}

void UnverifiedUserModel::deleteUnverifiedUser(const int userId_)
{
    int index_ = -1;

    for (int i = 0; i < unverifiedUsers_.size(); ++i)
    {
        if (userId_ == unverifiedUsers_[i].id_)
        {
            index_ = i;
            break;
        }
    }

    if (index_ >= 0 && index_ < unverifiedUsers_.size())
    {
        beginRemoveRows(QModelIndex(), index_, index_);
        unverifiedUsers_.remove(index_);
        endRemoveRows();
    }
}

bool UnverifiedUserModel::containsUnverifiedUser(const int userId_)
{
    auto it = std::find_if(unverifiedUsers_.begin(), unverifiedUsers_.end(), [userId_](const UnverifiedUsers& user_) {
        return user_.id_ == userId_;
    });

    return it != unverifiedUsers_.end();
}

int UnverifiedUserModel::getModelSize()
{
    return unverifiedUsers_.size();
}

void UnverifiedUserModel::clearUnverUser()
{
    if (unverifiedUsers_.isEmpty()) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, unverifiedUsers_.size() - 1);
    unverifiedUsers_.clear();
    endRemoveRows();
}
