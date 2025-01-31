#include "../../include/ConnectedUsers.h"
#include "../../include/Session.h"

ConnectedUsers::ConnectedUsers()
    : id_count_(0)
{}

ConnectedUsers::~ConnectedUsers()
{}

void ConnectedUsers::add_unauthorized_user(const Session& session_)
{
    id_count_++;

    if(unauthorie_users.find(id_count_) == unauthorie_users.end())
    {
        unauthorie_users.emplace(id_count_, session_);
    }
    else
    {
        add_unauthorized_user(session_);
    }
}

void ConnectedUsers::remove_unauthorized_user(const int id_)
{
    if(unauthorie_users.find(id_) != unauthorie_users.end())
    {
        unauthorie_users.erase(id_);
    }
}

void ConnectedUsers::add_authorize_user(const int id_, const Session& session_)
{
    if(authorize_users.find(id_) == authorize_users.end())
    {
        authorize_users.emplace(id_, session_);
    }
}

void ConnectedUsers::remove_authorize_user(const int id_)
{
    if(authorize_users.find(id_) != authorize_users.end())
    {
        authorize_users.erase(id_);
    }
}
