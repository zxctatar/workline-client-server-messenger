#ifndef SERVERSTRUCT_H
#define SERVERSTRUCT_H

#include <string>
#include "nlohmann/json.hpp""

struct ServerStruct {
    int serverID_;
    std::string serverName_;
    std::string serverDescription_;

    void to_json(nlohmann::json& j) const {
        j = nlohmann::json{
            {"id", serverID_},
            {"name", serverName_},
            {"description", serverDescription_}
        };
    }
};

#endif // SERVERSTRUCT_H
