#include "../include/ChatsManager.h"

ChatsManager::ChatsManager(QObject* parent)
    : QObject(parent)
{
}

ChatsManager::~ChatsManager()
{
}

ChatsManager& ChatsManager::instance()
{
    static ChatsManager instance_;
    return instance_;
}

void ChatsManager::addAvatar(const int userId_, const QString& avatarPath_)
{
    avatars_.insert(userId_, avatarPath_);
}

void ChatsManager::addChatAvatar(const int chatId_, const QString& avatarPath_)
{
    chatAvatars_.insert(chatId_, avatarPath_);
}

QString ChatsManager::getAvatar(const int userId_)
{
    auto it_ = avatars_.find(userId_);
    if(it_ != avatars_.end())
    {
        return it_.value();
    }
    return "";
}

void ChatsManager::clearAvatars()
{
    avatars_.clear();
    chatAvatars_.clear();
}
