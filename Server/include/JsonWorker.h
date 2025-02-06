#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <nlohmann/json.hpp>

class JsonWorker
{
public:
    explicit JsonWorker();

    nlohmann::json parceJson(const std::string& data_) const;

    std::string createUserIdJson(const int id_);

    ~JsonWorker();

private:

};

#endif // JSONWORKER_H
