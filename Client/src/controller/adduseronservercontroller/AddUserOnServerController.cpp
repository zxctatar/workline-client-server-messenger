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
