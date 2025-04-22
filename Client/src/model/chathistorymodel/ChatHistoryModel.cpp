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
    case Qt::UserRole + 4:
        return message_.viewed_;
    case Qt::UserRole + 5:
        return message_.time_;
    case Qt::UserRole + 6:
        return message_.messageId_;
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
    roles_[Qt::UserRole + 4] = "isViewed";
    roles_[Qt::UserRole + 5] = "time";
    roles_[Qt::UserRole + 6] = "messageId";
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
        messages_.append({messageId_, senderId_, message_, time_, avatarPath_, isCompanion_, viewed_, showAvatar_});
        endInsertRows();
    }
}

void ChatHistoryModel::clearMessages()
{
    beginRemoveRows(QModelIndex(), 0, messages_.size() - 1);
    messages_.clear();
    endRemoveRows();
}

void ChatHistoryModel::markMessage(const int messageId_, const bool viewed_)
{
    auto it_ = std::find_if(messages_.begin(), messages_.end(), [messageId_](const Message& mess_){
        return mess_.messageId_ == messageId_;
    });

    if(it_ != messages_.end())
    {
        int row_ = std::distance(messages_.begin(), it_);

        it_->viewed_ = viewed_;

        QVector<int> roles_;
        roles_ << Qt::UserRole + 4;

        emit dataChanged(index(row_), index(row_), roles_);
    }
}
