#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "JsonWorker.h"
#include "DBConnectionPool.h"
#include "UserDBManager.h"
#include <nlohmann/json.hpp>

class RequestRouter
{
public:
    explicit RequestRouter();
    ~RequestRouter();

    std::string defineQuery(const int userID_, const nlohmann::json& json_, DBConnectionPool& connectionPool_);

private:
    JsonWorker jsonWorker_;
    UserDBManager userManager_;
};

#endif // REQUESTROUTER_H
