#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>

class ServerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ServerModel(QObject* parent = nullptr);
    ~ServerModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addServer(const int id_, const QString& name, const QString& description_);

private:
    struct Server {
        int id_;
        QString name_;
        QString description_;
    };

    QVector<Server> servers_;
};

#endif // SERVERMODEL_H
