#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "ImageWorker.h"
#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>
#include <QImage>

class ServerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ServerModel(QObject* parent = nullptr);
    ~ServerModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addServer(const int id_, const QImage& image_, const QString& name, const QString& fullName_, const QString& description_);
    void deleteServer(const int serverId_);

private:
    struct Server {
        int id_;
        QImage image_;
        QString tempImagePath_;
        QString name_;
        QString fullName_;
        QString description_;
    };

    QVector<Server> servers_;
    ImageWorker imageWorker_;
};

#endif // SERVERMODEL_H
