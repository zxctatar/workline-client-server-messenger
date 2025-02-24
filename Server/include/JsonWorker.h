#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <nlohmann/json.hpp>

class JsonWorker
{
public:
    explicit JsonWorker();

    nlohmann::json parceJson(const std::string& data_) const;

    std::string createUserIdJson(const int id_);
    std::string createRegistrationCodeJson(const std::string& code_);
    std::string createLoginCodeJson(const std::string& code_);

    ~JsonWorker();

private:

};

#endif // JSONWORKER_H
