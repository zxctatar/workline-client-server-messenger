#ifndef CHATHISTORYMODEL_H
#define CHATHISTORYMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>

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

private:
    struct Message
    {

    };

    QVector<Message> messages_;
};

#endif // CHATHISTORYMODEL_H
