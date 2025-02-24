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

std::string JsonWorker::createLoginCodeJson(const std::string& code_)
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
