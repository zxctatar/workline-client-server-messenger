#include "../../../include/ServerModel.h"

ServerModel::ServerModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ServerModel::~ServerModel()
{
}

int ServerModel::rowCount(const QModelIndex& parent_) const
{
    Q_UNUSED(parent_);
    return servers_.size();
}

QVariant ServerModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= servers_.size())
    {
        return QVariant();
    }

    const Server& server_ = servers_.at(index_.row());

    switch(role_)
    {
    case Qt::DisplayRole:
        return server_.name_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ServerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::BackgroundRole] = "color";
    return roles;
}

void ServerModel::addServer(const int id_, const QString& name_, const QString& description_)
{
    beginInsertRows(QModelIndex(), servers_.size(), servers_.size());
    servers_.append({id_, name_, description_});
    endInsertRows();
}
