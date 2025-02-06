#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <qqml.h>

class UserModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UserModel(QObject* parent = nullptr);
    ~UserModel();

public slots:
    void setId(const int received_id_);

private:
    int id_;
};

#endif // USERMODEL_H
