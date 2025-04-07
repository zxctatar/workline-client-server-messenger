#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "JsonWorker.h"
#include "DBConnectionPool.h"
#include "UserDBManager.h"
#include "ConnectedUsers.h"
#include "ServerDBManager.h"
#include "ChatsDBManager.h"
#include <nlohmann/json.hpp>

class Session;

class RequestRouter
{
public:
    explicit RequestRouter();
    ~RequestRouter();

    void defineQuery(const boost::asio::any_io_executor& executor_, const int userID_, const nlohmann::json& json_, DBConnectionPool& connectionPool_, std::weak_ptr<Session> session_, ConnectedUsers& connUsers_);

private:
    JsonWorker jsonWorker_;
    UserDBManager userManager_;
    ServerDBManager serverManager_;
    ChatsDBManager chatManager_;
};

#endif // REQUESTROUTER_H
