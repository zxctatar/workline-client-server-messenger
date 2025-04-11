#include "../../../include/CandidateUserModel.h"
#include <algorithm>

CandidateUserModel::CandidateUserModel(const int serverId_, QObject* parent)
    : QAbstractListModel(parent)
    , serverId_(serverId_)
{
}

CandidateUserModel::~CandidateUserModel()
{
}

int CandidateUserModel::rowCount(const QModelIndex& parent_) const
{
    Q_UNUSED(parent_);
    return candidateUsers_.size();
}

QVariant CandidateUserModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= candidateUsers_.size())
    {
        return QVariant();
    }

    const CandidateUser& user_ = candidateUsers_.at(index_.row());

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

QHash<int, QByteArray> CandidateUserModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::UserRole + 1] = "id";
    return roles;
}

void CandidateUserModel::addCandidateUser(const int userId_, const QString& firstName_, const QString& lastName_, const QString& middleName_)
{
    if(containsCandidateUser(userId_))
    {
        return;
    }

    QString displayName_ = lastName_ + ' ' + firstName_[0] + ". " + middleName_[0] + '.';

    beginInsertRows(QModelIndex(), candidateUsers_.size(), candidateUsers_.size());
    candidateUsers_.append({userId_, firstName_, lastName_, middleName_, displayName_});
    endInsertRows();
}

bool CandidateUserModel::containsCandidateUser(const int userId_)
{
    auto it = std::find_if(candidateUsers_.begin(), candidateUsers_.end(), [userId_](const CandidateUser& user_) {
        return userId_ == user_.id_;
    });

    return it != candidateUsers_.end();
}

void CandidateUserModel::clearCandidateUsers()
{
    if(candidateUsers_.isEmpty())
    {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, candidateUsers_.size() - 1);
    candidateUsers_.clear();
    endRemoveRows();
}

void CandidateUserModel::deleteCandidateUser(const int receivedUserId_, const int receivedServerId_)
{
    if(receivedServerId_ == serverId_)
    {
        int index_ = -1;

        for(int i = 0; i < candidateUsers_.size(); ++i)
        {
            if(receivedUserId_ == candidateUsers_[i].id_)
            {
                index_ = i;
                break;
            }
        }

        if(index_ != -1)
        {
            beginRemoveRows(QModelIndex(), index_, index_);
            candidateUsers_.remove(index_);
            endRemoveRows();
        }
    }
}
