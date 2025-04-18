#ifndef CHATHISTORYMODEL_H
#define CHATHISTORYMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>
#include "SelectedChatManager.h"
#include "SelectedServerManager.h"

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
    void addMessage(const int serverId_, const int chatId_, const int messageId_, const QString& message_, const QString& time_, const bool isCompanion_, const bool viewed_);
    void clearMessages();

private:
    struct Message
    {
        QString message_;
        QString time_;
        bool isCompanion_;
        bool viewed_;
    };

    QVector<Message> messages_;
};

#endif // CHATHISTORYMODEL_H
