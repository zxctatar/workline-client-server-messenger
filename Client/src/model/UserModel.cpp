#include "../../include/UserModel.h"

UserModel::UserModel(QObject* parent)
    : QObject(parent)
    , id_(0)
{
}

UserModel::~UserModel()
{
}

void UserModel::setId(const int received_id_)
{
    id_ = received_id_;

    qDebug() << "Id = " << id_;
}
