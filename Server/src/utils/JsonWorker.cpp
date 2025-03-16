#include "../../include/JsonWorker.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

JsonWorker::JsonWorker()
{}

JsonWorker::~JsonWorker()
{}

nlohmann::json JsonWorker::parceJson(const std::string& data_) const
{
    try
    {
        nlohmann::json request_ = nlohmann::json::parse(data_);
        return request_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createUserIdJson(const int id_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "UserID";
        json_["ID"] = id_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createRegistrationCodeJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Registration";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createLoginSuccessJson(const std::string& code_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& email_, const std::string& phoneNumber_, const int userID_, const std::string& userRole_, const std::string& userLogin_, const std::string& userPassword_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Login";
        json_["Code"] = code_;
        json_["UserFirstName"] = firstName_;
        json_["UserLastName"] = lastName_;
        json_["UserMiddleName"] = middleName_;
        json_["UserEmail"] = email_;
        json_["UserPhoneNumber"] = phoneNumber_;
        json_["UserId"] = userID_;
        json_["UserRole"] = userRole_;
        json_["UserLogin"] = userLogin_;
        json_["UserPassword"] = userPassword_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createLoginUnsuccessJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Login";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createAddingServerSuccessJson(const std::string& code_, const int serverID_, const std::string& serverName_, const std::string& serverDescription_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_Server";
        json_["Code"] = code_;
        json_["ServerID"] = serverID_;
        json_["ServerName"] = serverName_;
        json_["ServerDescription"] = serverDescription_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}
std::string JsonWorker::createAddingServerUnsuccessJson(const std::string& code_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Add_Server";
        json_["Code"] = code_;
        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

std::string JsonWorker::createGetServersJson(const std::vector<ServerStruct> servers_)
{
    try
    {
        nlohmann::json json_;
        json_["Info"] = "Get_Servers";

        for(const auto& i : servers_)
        {
            nlohmann::json jsonServer_;
            i.to_json(jsonServer_);
            json_["Servers"].push_back(jsonServer_);
        }

        return json_.dump();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}
