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

    const Chat& chat_ = chats_.at(index_.row());

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
    case Qt::UserRole + 5:
        return chat_.avatarPath_;
    case Qt::UserRole + 6:
        return chat_.isGroupChat_;
    case Qt::UserRole + 7:
        return chat_.newMessagesCount_;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles_;
    roles_[Qt::DisplayRole] = "name";
    roles_[Qt::UserRole + 1] = "isChat";
    roles_[Qt::UserRole + 2] = "lastMess";
    roles_[Qt::UserRole + 3] = "id";
    roles_[Qt::UserRole + 4] = "companionId";
    roles_[Qt::UserRole + 5] = "imagePath";
    roles_[Qt::UserRole + 6] = "isGroupChat";
    roles_[Qt::UserRole + 7] = "newMessageCount";
    return roles_;
}

void ChatModel::addChat(const int companionId_, const int chatId_, const QImage& image_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const QString& lastMessage_, const QString& messageTime_, const bool isChat_, const bool isGroupChat_, const int newMessagesCount_)
{
    QString imagePath_ = imageWorker_.saveImageToTempFile(image_);

    ChatsManager::instance().addAvatar(companionId_, imagePath_);

    QString displayName_ = lastName_ + ' ' + firstName_;

    beginInsertRows(QModelIndex(), chats_.size(), chats_.size());
    chats_.append({displayName_, imagePath_, companionId_, chatId_, firstName_, lastName_, middleName_, lastMessage_, messageTime_, isChat_, isGroupChat_, newMessagesCount_});
    endInsertRows();
}

int ChatModel::getSize()
{
    return chats_.size();
}

void ChatModel::chatCreated(const int serverId_, const int companionId_, const int chatId_)
{
    int currentServerId_ = SelectedServerManager::instance().getServerId();

    if(serverId_ == currentServerId_)
    {
        auto it_ = std::find_if(chats_.begin(), chats_.end(), [companionId_](const Chat& privateChat_){
            return privateChat_.companionId_ == companionId_;
        });

        if(it_ != chats_.end())
        {
            int row = std::distance(chats_.begin(), it_);

            it_->isChat_ = true;
            it_->chatId_ = chatId_;

            QVector<int> roles_;
            roles_ << Qt::UserRole + 1 << Qt::UserRole + 3;

            emit dataChanged(index(row), index(row), roles_);
        }
    }
}

void ChatModel::clearChats()
{
    if(chats_.isEmpty())
    {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, chats_.size() - 1);
    chats_.clear();
    ChatsManager::instance().clearAvatars();
    endRemoveRows();
}

void ChatModel::updateLastMessage(const int serverId_, const int chatId_, const QString& lastMessage_)
{
    if(SelectedServerManager::instance().getServerId() == serverId_)
    {
        auto it_ = std::find_if(chats_.begin(), chats_.end(), [this, chatId_](const Chat& chat_){
            return chat_.chatId_ == chatId_;
        });

        if(it_ != chats_.end())
        {
            int row_ = std::distance(chats_.begin(), it_);

            it_->lastMessage_ = lastMessage_;

            QVector<int> roles_;
            roles_ << Qt::UserRole + 2;

            emit dataChanged(index(row_), index(row_), roles_);
        }
    }
}

void ChatModel::increaseMessageCount(const int chatId_)
{
    auto it_ = std::find_if(chats_.begin(), chats_.end(), [this, chatId_](const Chat& chat_){
        return chat_.chatId_ == chatId_;
    });

    if(it_ != chats_.end())
    {
        int row_ = std::distance(chats_.begin(), it_);

        it_->newMessagesCount_++;

        qDebug() << it_->newMessagesCount_;

        QVector<int> roles_;
        roles_ << Qt::UserRole + 7;

        emit dataChanged(index(row_), index(row_), roles_);
    }
}

void ChatModel::decreaseMessageCount(const int chatId_)
{
    auto it_ = std::find_if(chats_.begin(), chats_.end(), [this, chatId_](const Chat& chat_){
        return chat_.chatId_ == chatId_;
    });

    if(it_ != chats_.end())
    {
        int row_ = std::distance(chats_.begin(), it_);

        it_->newMessagesCount_--;

        qDebug() << it_->newMessagesCount_;

        QVector<int> roles_;
        roles_ << Qt::UserRole + 7;

        emit dataChanged(index(row_), index(row_), roles_);
    }
}
