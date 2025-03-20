#include "../include/ApplicationPageController.h"

ApplicationPageController::ApplicationPageController(QObject* parent)
    : QObject(parent)
    , unverUserModel_(std::make_shared<UnverifiedUserModel>())
{
}

ApplicationPageController::~ApplicationPageController()
{
    deleteUnverUserManager();
}

void ApplicationPageController::deleteUnverUserManager()
{
    if(unverUserModel_)
    {
        unverUserModel_.reset();
    }
}

UnverifiedUserModel* ApplicationPageController::getUnverUserModel() const
{
    return unverUserModel_.get();
}

void ApplicationPageController::getUnverUsers()
{
    QString request_ = jsonWorker_.createJsonGetUnverUsers();

    emit getUnverUsersSignal(request_);
}

void ApplicationPageController::refreshUnverUsers()
{
    unverUserModel_->clearUnverUser();

    QString request_ = jsonWorker_.createJsonGetUnverUsers();

    emit getUnverUsersSignal(request_);
}

void ApplicationPageController::slotUnverUsersProcessing(const QJsonObject& jsonObj_) const
{

    QJsonArray jsonArray_ = jsonObj_["UnverUsers"].toArray();

    for(const QJsonValue& value : jsonArray_)
    {
        if(!value.isObject())
        {
            continue;
        }

        QJsonObject userObject_ = value.toObject();

        int userId_ = userObject_["userId"].toInt();
        QString firstName_ = userObject_["firstName"].toString();
        QString lastName_ = userObject_["lastName"].toString();
        QString middleName_ = userObject_["middleName"].toString();

        unverUserModel_->addUnverifiedUser(userId_, firstName_, lastName_, middleName_);
    }
}

void ApplicationPageController::slotApproveUserProcessing(const QJsonObject& jsonObj_) const
{
    if(jsonObj_["code"] == "ALREADY_APPROVED")
    {
        emit alreadyApprovedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "APPROVED")
    {
        emit approvedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "ALREADY_REJECTED")
    {
        emit alreadyRejectedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "ERROR")
    {
        emit errorSignal();
    }
}

void ApplicationPageController::slotRejectUserProcessing(const QJsonObject& jsonObj_) const
{
    if(jsonObj_["code"] == "ALREADY_REJECTED")
    {
        emit alreadyRejectedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "REJECTED")
    {
        emit rejectedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "ALREADY_APPROVED")
    {
        emit alreadyApprovedSignal();
        unverUserModel_->deleteUnverifiedUser(jsonObj_["userId"].toInt());
    }
    else if(jsonObj_["code"] == "ERROR")
    {
        emit errorSignal();
    }
}

void ApplicationPageController::slotDeleteUnverUser(const int userId_) const
{
    unverUserModel_->deleteUnverifiedUser(userId_);
}

void ApplicationPageController::approveUser(const int userId_)
{
    QString request_ = jsonWorker_.createJsonApproveUser(userId_);

    emit approveUserSignal(request_);
}

void ApplicationPageController::rejectUser(const int userId_)
{
    QString request_ = jsonWorker_.createJsonRejectUser(userId_);

    emit rejectUserSignal(request_);
}

