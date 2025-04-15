#include "../../../include/SelectedChatManager.h"

SelectedChatManager::SelectedChatManager(QObject* parent)
    : QObject(parent)
    , chatId_(-1)
{
}

SelectedChatManager::~SelectedChatManager()
{
}

SelectedChatManager& SelectedChatManager::instance()
{
    static SelectedChatManager instance_;
    return instance_;
}

void SelectedChatManager::setChatId(const int chatId_)
{
    this->chatId_ = chatId_;
    emit setNewChatIdSignal(chatId_);
}

int SelectedChatManager::getChatId()
{
    return chatId_;
}
