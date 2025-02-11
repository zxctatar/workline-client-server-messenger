#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "JsonWorker.h"
#include <nlohmann/json.hpp>

class RequestRouter
{
public:
    explicit RequestRouter();
    ~RequestRouter();

    std::string defineQuery(const int userID_, const nlohmann::json& json_);

private:
    JsonWorker jsonWorker_;
};

#endif // REQUESTROUTER_H
