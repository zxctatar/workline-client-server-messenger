#include "../../include/UserModel.h"

UserModel::UserModel(QObject* parent)
    : QObject(parent)
    , id_(0)
{
}

UserModel::~UserModel()
{
}

void UserModel::requestIdSlot()
{
    if(id_ == 0)
    {
        emit getIdSignal("GET_ID");
    }
}

void UserModel::setIdSlot(const int received_id_)
{
    id_ = received_id_;
    qDebug() << id_;
}
