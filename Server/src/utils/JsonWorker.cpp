#include "../../include/JsonWorker.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

JsonWorker::JsonWorker()
{}

nlohmann::json JsonWorker::parceJson(const std::string& data_) const
{
    try
    {
        auto request_ = nlohmann::json::parse(data_);
        return request_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return nullptr;
    }
}

JsonWorker::~JsonWorker()
{}

