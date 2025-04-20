#include "../../../include/SelectedChatManager.h"
#include <QDebug>

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

void SelectedChatManager::setChatData(const QString& receivedFirstName_, const QString& receivedLastName_, const QString& receivedMiddleName_, const QString& receivedBirthDate_, const QString& receivedEmail_, const QString& receivedPhoneNumber_)
{
    isGroupChat_ = false;
    firstName_ = receivedFirstName_;
    lastName_ = receivedLastName_;
    middleName_ = receivedMiddleName_;
    email_ = receivedEmail_;
    birthDate_ = receivedBirthDate_;
    phoneNumber_ = receivedPhoneNumber_;

    emit chatDataChangedSignal();
}

void SelectedChatManager::setChatAvatar(const QString& avatarPath_)
{
    this->avatarPath_ = avatarPath_;

    emit chatAvatarChangedSignal();
}

void SelectedChatManager::clearChatData()
{
    avatarPath_ = "";
    firstName_ = "";
    lastName_ = "";
    middleName_ = "";
    email_ = "";
    birthDate_ = "";
    phoneNumber_ = "";

    emit clearChatDataSignal();
}

QString SelectedChatManager::getAvatarPath() const
{
    return avatarPath_;
}

QString SelectedChatManager::getFirstName() const
{
    return firstName_;
}

QString SelectedChatManager::getLastName() const
{
    return lastName_;
}

QString SelectedChatManager::getMiddleName() const
{
    return middleName_;
}

QString SelectedChatManager::getBirthDate() const
{
    return birthDate_;
}

QString SelectedChatManager::getEmail() const
{
    return email_;
}

QString SelectedChatManager::getPhoneNumber() const
{
    return phoneNumber_;
}

bool SelectedChatManager::getGroup() const
{
    return isGroupChat_;
}

