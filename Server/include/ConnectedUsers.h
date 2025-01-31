#ifndef CONNECTEDUSERS_H
#define CONNECTEDUSERS_H

#include <boost/uuid/uuid_generators.hpp>
#include <map>

class Session;

class ConnectedUsers
{
public:
    explicit ConnectedUsers();
    ~ConnectedUsers();

    void add_unauthorized_user(const Session& session_);
    void remove_unauthorized_user(const int id_);

    void add_authorize_user(const int id_, const Session& session_);
    void remove_authorize_user(const int id_);

private:
    std::map<int, Session&> authorize_users;
    std::map<int, Session&> unauthorie_users;

    int id_count_;
};

#endif // CONNECTEDUSERS_H
