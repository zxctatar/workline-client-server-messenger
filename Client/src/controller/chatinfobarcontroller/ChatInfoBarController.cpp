#include "../include/ChatInfoBarController.h"

ChatInfoBarController::ChatInfoBarController(QObject* parent)
    : QObject(parent)
{
}

ChatInfoBarController::~ChatInfoBarController()
{
}

void ChatInfoBarController::slotSetChatData()
{
    bool isGroupChat_ = SelectedChatManager::instance().getGroup();
    QString firstName_ = SelectedChatManager::instance().getFirstName();
    QString lastName_ = SelectedChatManager::instance().getLastName();
    QString middleName_ = SelectedChatManager::instance().getMiddleName();
    QString email_ = SelectedChatManager::instance().getEmail();
    QString phoneNumber_ = SelectedChatManager::instance().getPhoneNumber();
    QDate date_ = QDate::fromString(SelectedChatManager::instance().getBirthDate(), "yyyy-MM-dd");
    QString birthDate_ = date_.toString("dd-MM-yyyy");

    emit setChatDataSignal(firstName_, lastName_, middleName_, email_, phoneNumber_, birthDate_, isGroupChat_);
}

void ChatInfoBarController::slotSetChatAvatar()
{
    QString avatarPath_ = SelectedChatManager::instance().getAvatarPath();

    emit setChatAvatarSignal(avatarPath_);
}

void ChatInfoBarController::slotClearChatData()
{
    emit clearChatDataSignal();
}

void ChatInfoBarController::getChatId()
{
    int chatId_ = SelectedChatManager::instance().getChatId();

    emit setChatIdSignal(chatId_);
}

void ChatInfoBarController::slotChatIdChanged(const int chatId_)
{
    emit setChatIdSignal(chatId_);
}

void ChatInfoBarController::slotServerChanged(const int serverId_)
{
    Q_UNUSED(serverId_);

    emit clearChatIdSignal();
}
