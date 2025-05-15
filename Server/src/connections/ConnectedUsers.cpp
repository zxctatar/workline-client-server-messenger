#include "../../include/ConnectedUsers.h"
#include "../../include/Session.h"
#include <iostream>

ConnectedUsers::ConnectedUsers()
    : id_count_(0)
{}

ConnectedUsers::~ConnectedUsers()
{}

void ConnectedUsers::addAuthorizeUser(const int id_, std::weak_ptr<Session> session_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(authorized_users.find(id_) == authorized_users.end())
    {
        session_.lock()->setAccountId(id_);
        authorized_users.emplace(id_, session_);
    }
}

void ConnectedUsers::addAuthorizeAdmin(const int id_, std::weak_ptr<Session> session_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(authorized_admins.find(id_) == authorized_admins.end())
    {
        session_.lock()->setAccountId(id_);
        authorized_admins.emplace(id_, session_);
    }
}

void ConnectedUsers::reconnectUser(const int id_, std::weak_ptr<Session> session_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    session_.lock()->setAccountId(id_);
    authorized_users[id_] = session_;
}

void ConnectedUsers::reconnectAdmin(const int id_, std::weak_ptr<Session> session_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    session_.lock()->setAccountId(id_);
    authorized_admins[id_] = session_;
}

void ConnectedUsers::removeAuthorize(const int id_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    authorized_users.erase(id_);
    authorized_admins.erase(id_);
}

std::unordered_map<int, std::weak_ptr<Session>> ConnectedUsers::getAuthorizeUsers() const
{
    return authorized_users;
}

std::unordered_map<int, std::weak_ptr<Session>> ConnectedUsers::getAuthorizeAdmins() const
{
    return authorized_admins;
}

std::weak_ptr<Session> ConnectedUsers::getUser(const int id_) const
{
    auto itUser_ = authorized_users.find(id_);

    if(itUser_ != authorized_users.end())
    {
        return authorized_users.at(id_);
    }

    auto itAdmin_ = authorized_admins.find(id_);

    if(itAdmin_ != authorized_admins.end())
    {
        return authorized_admins.at(id_);
    }

    return {};
}

