#include "../../../include/ChatHistoryModel.h"

ChatHistoryModel::ChatHistoryModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ChatHistoryModel::~ChatHistoryModel()
{
}

QVariant ChatHistoryModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= messages_.size())
    {
        return QVariant();
    }

    const Message message_ = messages_.at(index_.row());

    switch(role_)
    {
    case Qt::DisplayRole:
        return QVariant();
    default:
        return QVariant();
    }
}

int ChatHistoryModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return messages_.size();
}

QHash<int, QByteArray> ChatHistoryModel::roleNames() const
{
    QHash<int, QByteArray> roles_;
    return roles_;
}
