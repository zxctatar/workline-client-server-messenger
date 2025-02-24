#include "../../include/RequestRouter.h"
#include <memory>

RequestRouter::RequestRouter()
{
}

RequestRouter::~RequestRouter()
{
}

std::string RequestRouter::defineQuery(const int userID_, const nlohmann::json& json_, DBConnectionPool& connectionPool_)
{
    if(json_["Info"] == "GET_ID")
    {
        std::string responseJson_ = jsonWorker_.createUserIdJson(userID_);

        return responseJson_;
    }
    else if(json_["Info"] == "Registration")
    {
        if(!json_.contains("lastname") || !json_.contains("firstname") ||
           !json_.contains("middlename") || !json_.contains("login") ||
           !json_.contains("phonenumber") || !json_.contains("email") ||
           !json_.contains("password"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string lastname_ = json_["lastname"].get<std::string>();
        std::string firstname_ = json_["firstname"].get<std::string>();
        std::string middlename_ = json_["middlename"].get<std::string>();
        std::string login_ = json_["login"].get<std::string>();
        long long int phonenumber_ = std::stoll(json_["phonenumber"].get<std::string>());
        std::string email_ = json_["email"].get<std::string>();
        std::string password_ = json_["password"].get<std::string>();

        std::string response_ = userManager_.regUser(connection_, lastname_, firstname_, middlename_, login_, phonenumber_, email_, password_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createRegistrationCodeJson(response_);
        return responseJson_;
    }
    else if(json_["Info"] == "Login")
    {
        if(!json_.contains("login") || !json_.contains("password"))
        {
            throw std::runtime_error("Lost the value in the json document");
        }

        auto connection_ = connectionPool_.getConnection();

        std::string login_ = json_["login"].get<std::string>();
        std::string password_ = json_["password"].get<std::string>();

        std::string response_ = userManager_.loginUser(connection_, login_, password_);
        connectionPool_.returnConnection(connection_);

        std::string responseJson_ = jsonWorker_.createLoginCodeJson(response_);
        return responseJson_;
    }
    else
    {
        return "0";
    }
}
