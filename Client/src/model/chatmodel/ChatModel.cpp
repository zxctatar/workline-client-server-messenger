#include "../../../include/ChatModel.h"
#include <algorithm>

ChatModel::ChatModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ChatModel::~ChatModel()
{
}

int ChatModel::rowCount(const QModelIndex& parent_) const
{
    Q_UNUSED(parent_);
    return chats_.size();
}

QVariant ChatModel::data(const QModelIndex& index_, int role_) const
{
    if(!index_.isValid() || index_.row() >= chats_.size())
    {
        return QVariant();
    }

    const PrivateChat& chat_ = chats_.at(index_.row());

    switch(role_)
    {
    case Qt::DisplayRole:
        return chat_.displayName_;
    case Qt::UserRole + 1:
        return chat_.isChat_;
    case Qt::UserRole + 2:
        return chat_.lastMessage_;
    case Qt::UserRole + 3:
        return chat_.chatId_;
    case Qt::UserRole + 4:
        return chat_.companionId_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::UserRole + 1] = "isChat";
    roles[Qt::UserRole + 2] = "lastMessage";
    roles[Qt::UserRole + 3] = "id";
    roles[Qt::UserRole + 4] = "companionId";
    return roles;
}

void ChatModel::addChat(const int companionId_, const int chatId_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const QString& lastMessage_, const QString& messageTime_, const bool isChat_)
{
    QString displayName_ = lastName_ + ' ' + firstName_;

    beginInsertRows(QModelIndex(), chats_.size(), chats_.size());
    chats_.append({displayName_, companionId_, chatId_, firstName_, lastName_, middleName_, lastMessage_, messageTime_, isChat_});
    endInsertRows();
}

int ChatModel::getSize()
{
    return chats_.size();
}

void ChatModel::deleteChats()
{
    beginRemoveRows(QModelIndex(), 0, chats_.size() - 1);
    chats_.clear();
    endRemoveRows();
}

void ChatModel::chatCreated(const int serverId_, const int companionId_, const int chatId_)
{
    int currentServerId_ = SelectedServerManager::instance().getServerId();

    if(serverId_ == currentServerId_)
    {
        auto it_ = std::find_if(chats_.begin(), chats_.end(), [companionId_](const PrivateChat& privateChat_){
            return privateChat_.companionId_ == companionId_;
        });

        if(it_ != chats_.end())
        {
            int row = std::distance(chats_.begin(), it_);

            it_->isChat_ = true;
            it_->chatId_ = chatId_;

            QVector<int> roles;
            roles << Qt::UserRole + 1 << Qt::UserRole + 3;

            emit dataChanged(index(row), index(row), roles);
        }
    }
}
