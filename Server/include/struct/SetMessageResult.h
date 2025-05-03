#ifndef SETMESSAGERESULT_H
#define SETMESSAGERESULT_H

#include <string>
#include <vector>

struct SetMessageResult
{
    int messageId_;
    std::string message_;
    std::string time_;
    std::vector<int> companions_;
};

#endif // SETMESSAGERESULT_H
