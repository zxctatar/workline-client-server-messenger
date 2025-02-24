#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <qqml.h>
#include "JsonWorker.h"

class UserModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UserModel(QObject* parent = nullptr);
    ~UserModel();

public slots:
    void setIdSlot(const int received_id_);

private:
    int id_;
    JsonWorker jsonWorker_;
};

#endif // USERMODEL_H
