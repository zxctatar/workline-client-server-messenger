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
        return message_.message_;
    case Qt::UserRole + 1:
        return message_.isCompanion_;
    case Qt::UserRole + 2:
        return message_.avatarPath_;
    case Qt::UserRole + 3:
        return message_.showAvatar_;
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
    roles_[Qt::DisplayRole] = "messages";
    roles_[Qt::UserRole + 1] = "companion";
    roles_[Qt::UserRole + 2] = "avatarPath";
    roles_[Qt::UserRole + 3] = "showAvatar";
    return roles_;
}

void ChatHistoryModel::addMessage(const int senderId_, const int serverId_, const int chatId_, const int messageId_, const QString& message_, const QString& time_, const bool isCompanion_, const bool viewed_)
{
    bool showAvatar_ = false;

    if(messages_.size() == 0)
    {
        showAvatar_ = true;
    }
    else if(messages_.last().senderId_ == senderId_)
    {
        int row_ = std::distance(messages_.begin(), messages_.end() - 1);

        messages_.last().showAvatar_ = false;

        QVector<int> roles_;
        roles_ << Qt::UserRole + 3;

        emit dataChanged(index(row_), index(row_), roles_);

        showAvatar_ = true;
    }
    else if(messages_.last().senderId_ != senderId_)
    {
        showAvatar_ = true;
    }

    QString avatarPath_ = ChatsManager::instance().getAvatar(senderId_);

    if(serverId_ == SelectedServerManager::instance().getServerId() && chatId_ == SelectedChatManager::instance().getChatId())
    {
        beginInsertRows(QModelIndex(), messages_.size(), messages_.size());
        messages_.append({senderId_, message_, time_, avatarPath_, isCompanion_, viewed_, showAvatar_});
        endInsertRows();
    }
}

void ChatHistoryModel::clearMessages()
{
    beginRemoveRows(QModelIndex(), 0, messages_.size() - 1);
    messages_.clear();
    endRemoveRows();
}
