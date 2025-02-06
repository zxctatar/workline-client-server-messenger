#include "../../include/ConnectedUsers.h"
#include "../../include/Session.h"

ConnectedUsers::ConnectedUsers()
    : id_count_(0)
{}

ConnectedUsers::~ConnectedUsers()
{}

void ConnectedUsers::addUnauthorizedUser(std::shared_ptr<Session> session_)
{
    id_count_++;

    while(unauthorized_users.find(id_count_) != unauthorized_users.end())
    {
        id_count_++;
    }
    session_->setAccountId(id_count_);
    unauthorized_users.emplace(id_count_, session_);
}

void ConnectedUsers::removeUnauthorizedUser(const int id_)
{
    unauthorized_users.erase(id_);
}

void ConnectedUsers::addAuthorizeUser(const int id_, std::shared_ptr<Session> session_)
{
    if(authorized_users.find(id_) == authorized_users.end())
    {
        session_->setAccountId(id_);
        authorized_users.emplace(id_, session_);
    }
}

void ConnectedUsers::removeAuthorizeUser(const int id_)
{
    authorized_users.erase(id_);
}
