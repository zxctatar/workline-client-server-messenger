#ifndef CANDIDATEUSERMODEL_H
#define CANDIDATEUSERMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>
#include "ImageWorker.h"

class CandidateUserModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CandidateUserModel(const int serverId_, QObject* parent = nullptr);
    ~CandidateUserModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addCandidateUser(const int userId_, const QImage& image_, const QString& firstName_, const QString& lastName_, const QString& middleName_);
    void deleteCandidateUser(const int receivedUserId_, const int receivedServerId_);
    void clearCandidateUsers();

private:
    struct CandidateUser {
        int id_;
        QString imagePath_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        QString displayName_;
    };

    bool containsCandidateUser(const int userId_);

    int serverId_;
    QVector<CandidateUser> candidateUsers_;

    ImageWorker imageWorker_;
};

#endif // CANDIDATEUSERMODEL_H
