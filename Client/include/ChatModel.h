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
    void addChat(const int companionId_, const int chatId_, const QImage& image_, const QString& firstName_, const QString& lastName_, const QString& middleName_, const QString& lastMessage_, const QString& messageTime_, const bool isChat_, const bool isGroupChat_);
    int getSize();
    void chatCreated(const int serverId_, const int companionId_, const int chatId_);
    void clearChats();
    void updateLastMessage(const int serverId_, const int chatId_, const QString& lastMessage_);

private:
    struct Chat {
        QString displayName_;
        QString avatarPath_;
        int companionId_;
        int chatId_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        QString lastMessage_;
        QString messageTime_;
        bool isChat_;
        bool isGroupChat_;
    };

    QVector<Chat> chats_;

    ImageWorker imageWorker_;
};

#endif // CHATMODEL_H
