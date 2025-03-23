#include "../../../include/AddUserOnServerController.h"

AddUserOnServerController::AddUserOnServerController(QObject* parent)
    : QObject(parent)
    , candidateUserModel_(std::make_shared<CandidateUserModel>())
{
}

AddUserOnServerController::~AddUserOnServerController()
{
    if(candidateUserModel_)
    {
        candidateUserModel_.reset();
    }
}

CandidateUserModel* AddUserOnServerController::getCandidateUserModel()
{
    return candidateUserModel_.get();
}

void AddUserOnServerController::getCandidateUsers() const
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetCandidateUsers(serverId_);

    emit getCandidateUsersSignal(request_);
}

void AddUserOnServerController::slotCandidateUsersProcessing(const QJsonObject& jsonObj_) const
{
    int serverId_ = SelectedServerManager::instance().getServerId();

    if(jsonObj_["serverId"].toInt() == serverId_)
    {
        QJsonArray jsonArray_ = jsonObj_["CandidateUser"].toArray();

        for(const QJsonValue& val : jsonArray_)
        {
            if(!val.isObject())
            {
                continue;
            }

            QJsonObject obj_ = val.toObject();

            int userId_ = obj_["userId"].toInt();
            QString firstName_ = obj_["firstName"].toString();
            QString lastName_ = obj_["lastName"].toString();
            QString middleName_ = obj_["middleName"].toString();

            candidateUserModel_->addCandidateUser(userId_, firstName_, lastName_, middleName_);
        }
    }
}

void AddUserOnServerController::refreshCandidateUsers() const
{
    candidateUserModel_->clearCandidateUsers();

    int serverId_ = SelectedServerManager::instance().getServerId();

    QString request_ = jsonWorker_.createJsonGetCandidateUsers(serverId_);

    emit getCandidateUsersSignal(request_);
}
