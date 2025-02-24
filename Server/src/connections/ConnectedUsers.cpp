#include "../../include/ConnectedUsers.h"
#include "../../include/Session.h"

ConnectedUsers::ConnectedUsers()
    : id_count_(0)
{}

ConnectedUsers::~ConnectedUsers()
{}

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
