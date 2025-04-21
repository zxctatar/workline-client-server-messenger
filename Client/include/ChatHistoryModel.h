#ifndef CHATHISTORYMODEL_H
#define CHATHISTORYMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>
#include "SelectedChatManager.h"
#include "SelectedServerManager.h"
#include "ChatsManager.h"

class ChatHistoryModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ChatHistoryModel(QObject* parent = nullptr);
    ~ChatHistoryModel();

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    void addMessage(const int senderId_, const int serverId_, const int chatId_, const int messageId_, const QString& message_, const QString& time_, const bool isCompanion_, const bool viewed_);
    void clearMessages();
    void markMessage(const int messageId_, const bool viewed_);

private:
    struct Message
    {
        int messageId_;
        int senderId_;
        QString message_;
        QString time_;
        QString avatarPath_;
        bool isCompanion_;
        bool viewed_;
        bool showAvatar_;
    };

    QMap<int, QString> avatars_;
    QVector<Message> messages_;
};

#endif // CHATHISTORYMODEL_H
