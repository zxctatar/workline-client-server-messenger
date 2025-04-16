#include "../../../include/ServerModel.h"

ServerModel::ServerModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ServerModel::~ServerModel()
{
    imageWorker_.cleanupTempFiles();
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
        return QVariant(server_.tempImagePath_);
    case Qt::UserRole + 1:
        return server_.id_;
    case Qt::UserRole + 2:
        return server_.fullName_;
    case Qt::UserRole + 3:
        return server_.description_;
    case Qt::UserRole + 4:
        return server_.name_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ServerModel::roleNames() const
{
    QHash<int, QByteArray> roles_;
    roles_[Qt::DisplayRole] = "path";
    roles_[Qt::UserRole + 1] = "id";
    roles_[Qt::UserRole + 2] = "fullName";
    roles_[Qt::UserRole + 3] = "description";
    roles_[Qt::UserRole + 4] = "name";
    return roles_;
}

void ServerModel::addServer(const int id_, const QImage& image_, const QString& name_, const QString& fullName_, const QString& description_)
{
    QString imagePath_ = imageWorker_.saveImageToTempFile(image_);

    beginInsertRows(QModelIndex(), servers_.size(), servers_.size());
    servers_.append({id_, image_, imagePath_, name_, fullName_, description_});
    endInsertRows();
}

void ServerModel::deleteServer(const int serverId_)
{
    int index_ = -1;

    for(int i = 0; i < servers_.size(); ++i)
    {
        if(serverId_ == servers_[i].id_)
        {
            index_ = i;
            break;
        }
    }

    if(index_ == -1)
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index_, index_);
    servers_.remove(index_);
    endRemoveRows();
}
