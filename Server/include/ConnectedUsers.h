#ifndef CONNECTEDUSERS_H
#define CONNECTEDUSERS_H

#include <boost/uuid/uuid_generators.hpp>
#include <unordered_map>
#include <mutex>
#include <memory>

class Session;

class ConnectedUsers
{
public:
    explicit ConnectedUsers();
    ~ConnectedUsers();

    void addAuthorizeUser(const int id_, std::weak_ptr<Session> session_);
    void addAuthorizeAdmin(const int id_, std::weak_ptr<Session> session_);

    void reconnectUser(const int id_, std::weak_ptr<Session> session_);
    void reconnectAdmin(const int id_, std::weak_ptr<Session> session_);

    void removeAuthorize(const int id_);
    std::weak_ptr<Session> getUser(const int id_) const;

    std::unordered_map<int, std::weak_ptr<Session>> getAuthorizeUsers() const;
    std::unordered_map<int, std::weak_ptr<Session>> getAuthorizeAdmins() const;

private:
    std::unordered_map<int, std::weak_ptr<Session>> authorized_users;
    std::unordered_map<int, std::weak_ptr<Session>> authorized_admins;

    std::mutex mutex_;

    int id_count_;
};

#endif // CONNECTEDUSERS_H
