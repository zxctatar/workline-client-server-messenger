#ifndef CHATDATARESULT_H
#define CHATDATARESULT_H

#include <string>
#include "nlohmann/json.hpp"

struct ChatDataResult
{
    int userId_;
    std::string firstName_;
    std::string lastName_;
    std::string middleName_;
    std::string email_;
    std::string birthDate_;
    std::string phoneNumber_;
};

#endif // CHATDATARESULT_H
