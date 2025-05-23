#ifndef SELECTEDCHATMANAGER_H
#define SELECTEDCHATMANAGER_H

#include <QObject>

class SelectedChatManager : public QObject
{
    Q_OBJECT

public:
    static SelectedChatManager& instance();

    void setChatData(const QString& receivedFirstName_, const QString& receivedLastName_, const QString& receivedMiddleName_, const QString& receivedBirthDate_, const QString& receivedEmail_, const QString& receivedPhoneNumber_);
    void setGroupChatData(const QString& receivedGroupName_, const int usersCount_);
    void setChatId(const int chatId_);
    void setChatAvatar(const QString& avatarPath_);
    int getChatId();
    void clearChatData();
    void setIsGroup(const bool isGroup_);

    QString getAvatarPath() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getMiddleName() const;
    QString getBirthDate() const;
    QString getEmail() const;
    QString getPhoneNumber() const;
    bool getGroup() const;
    QString getGroupName() const;
    int getUsersCount() const;

signals:
    void setNewChatIdSignal(const int chatId_);
    void chatDataChangedSignal();
    void chatAvatarChangedSignal();
    void clearChatDataSignal();

private:
    explicit SelectedChatManager(QObject* parent = nullptr);
    ~SelectedChatManager();

    int chatId_;
    bool isGroupChat_;
    QString groupChatName_;
    QString avatarPath_;
    QString firstName_;
    QString lastName_;
    QString middleName_;
    QString birthDate_;
    QString email_;
    QString phoneNumber_;
    int usersCount_;
};

#endif // SELECTEDCHATMANAGER_H
