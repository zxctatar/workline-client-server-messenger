#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>
#include "SelectedServerManager.h"
#include "ImageWorker.h"
#include "ChatsManager.h"

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ChatModel(QObject* parent = nullptr);
    ~ChatModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addChat(const int companionId_, const int chatId_, const QImage& image_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const QString& lastMessage_, const QString& messageTime_, const bool isChat_, const bool isGroupChat_, const int newMessagesCount_);
    void addGroupChat(const int chatId_, const QString& chatName_, const QImage& image_, const QString& messageTime_, const QString& lastMessage_, const int newMessagsCount_);
    int getSize();
    void chatCreated(const int serverId_, const int companionId_, const int chatId_);
    void clearChats();
    void updateLastMessage(const int serverId_, const int chatId_, const QString& lastMessage_, const bool isGroup_);
    void increaseMessageCount(const int chatId_, const bool isGroup_);
    void decreaseMessageCount(const int chatId_, const bool isGroup_);
    void addNewGroupChat(const int chatId_, const int serverId_, const int ownerId_, const QString& groupName_, const QImage& groupAvatar_);

private:
    struct Chat {
        QString displayName_;
        QString avatarPath_;
        int companionId_;
        int chatId_;
        int ownerId_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        QString lastMessage_;
        QString messageTime_;
        bool isChat_;
        bool isGroupChat_;
        int newMessagesCount_;
    };

    QVector<Chat> chats_;

    ImageWorker imageWorker_;
};

#endif // CHATMODEL_H
