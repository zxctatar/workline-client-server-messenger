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
    return roles_;
}

void ChatHistoryModel::addMessage(const int serverId_, const int chatId_, const int messageId_, const QString& message_, const QString& time_, const bool isCompanion_, const bool viewed_)
{
    if(serverId_ == SelectedServerManager::instance().getServerId() && chatId_ == SelectedChatManager::instance().getChatId())
    {
        beginInsertRows(QModelIndex(), messages_.size(), messages_.size());
        messages_.append({message_, time_, isCompanion_, viewed_});
        endInsertRows();
    }
}

void ChatHistoryModel::clearMessages()
{
    beginRemoveRows(QModelIndex(), 0, messages_.size() - 1);
    messages_.clear();
    endRemoveRows();
}
