#ifndef UNVERIFIEDUSERMODEL_H
#define UNVERIFIEDUSERMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>
#include "ImageWorker.h"

class UnverifiedUserModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UnverifiedUserModel(QObject* parent = nullptr);
    ~UnverifiedUserModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addUnverifiedUser(const int id_, const QImage& avatar_, const QString& firstName_, const QString& lastName_, const QString& middleName_);
    int getModelSize();
    void deleteUnverifiedUser(const int userId_);
    void clearUnverUser();

private:
    bool containsUnverifiedUser(const int userId_);

    struct UnverifiedUsers {
        int id_;
        QString imagePath_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        QString displayName_;
    };

    QVector<UnverifiedUsers> unverifiedUsers_;
    ImageWorker imageWorker_;
};

#endif // UNVERIFIEDUSERMODEL_H
