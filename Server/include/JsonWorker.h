#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <nlohmann/json.hpp>

class JsonWorker
{
public:
    explicit JsonWorker();

    nlohmann::json parceJson(const std::string& data_) const;

    ~JsonWorker();

private:

};

#endif // JSONWORKER_H
