#ifndef SETMESSAGERESULT_H
#define SETMESSAGERESULT_H

#include <string>

struct SetMessageResult
{
    int messageId_;
    int companionId_;
    std::string message_;
    std::string time_;
};

#endif // SETMESSAGERESULT_H
