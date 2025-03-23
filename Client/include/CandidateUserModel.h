#ifndef CANDIDATEUSERMODEL_H
#define CANDIDATEUSERMODEL_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>

class CandidateUserModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CandidateUserModel(QObject* parent = nullptr);
    ~CandidateUserModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addCandidateUser(const int userId_, const QString& firstName_, const QString& lastName_, const QString& middleName_);
    void clearCandidateUsers();

private:
    struct CandidateUser {
        int id_;
        QString firstName_;
        QString lastName_;
        QString middleName_;
        QString displayName_;
    };

    bool containsCandidateUser(const int userId_);

    QVector<CandidateUser> candidateUsers_;
};

#endif // CANDIDATEUSERMODEL_H
