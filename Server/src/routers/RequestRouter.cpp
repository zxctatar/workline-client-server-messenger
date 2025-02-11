#include "../../include/RequestRouter.h"
#include <iostream>

RequestRouter::RequestRouter()
{
}

RequestRouter::~RequestRouter()
{
}

std::string RequestRouter::defineQuery(const int userID_, const nlohmann::json& json_)
{
    if(json_["Info"] == "GET_ID")
    {
        std::string response_ = jsonWorker_.createUserIdJson(userID_);

        return response_;
    }
    else
    {
        return "0";
    }
}
