#include "../../../include/CandidateUserModel.h"

CandidateUserModel::CandidateUserModel(QObject* parent)
    : QAbstractListModel(parent)
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
