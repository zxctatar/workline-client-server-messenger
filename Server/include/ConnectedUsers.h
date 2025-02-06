#ifndef CONNECTEDUSERS_H
#define CONNECTEDUSERS_H

#include <boost/uuid/uuid_generators.hpp>
#include <map>
#include <memory>

class Session;

class ConnectedUsers
{
public:
    explicit ConnectedUsers();
    ~ConnectedUsers();

    void addUnauthorizedUser(std::shared_ptr<Session> session_);
    void removeUnauthorizedUser(const int id_);

    void addAuthorizeUser(const int id_, std::shared_ptr<Session> session_);
    void removeAuthorizeUser(const int id_);

private:
    std::map<int, std::shared_ptr<Session>> authorized_users;
    std::map<int, std::shared_ptr<Session>> unauthorized_users;

    int id_count_;
};

#endif // CONNECTEDUSERS_H
