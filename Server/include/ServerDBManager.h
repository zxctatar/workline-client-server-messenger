#ifndef SERVERDBMANAGER_H
#define SERVERDBMANAGER_H

#include <string>
#include <memory>
#include "DBConnection.h"
#include "struct/AddResult.h"
#include "struct/ServerStruct.h"
#include "struct/ServerDeleteStruct.h"

class ServerDBManager
{
public:
    explicit ServerDBManager();
    ~ServerDBManager();

    AddResult addServer(std::shared_ptr<DBConnection> connection_, const std::string& serverName_, const std::string& serverDescription_) const;
    std::vector<ServerStruct> getServers(std::shared_ptr<DBConnection> connection_, const int userID_) const;
    ServerDeleteStruct deleteServer(std::shared_ptr<DBConnection> connection_, const int serverId_) const;

private:
};

#endif // SERVERDBMANAGER_H
