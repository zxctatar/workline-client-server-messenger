#ifndef SERVERDBMANAGER_H
#define SERVERDBMANAGER_H

#include <string>
#include <memory>
#include "DBConnection.h"
#include "struct/AddResult.h"
#include "struct/ServerStruct.h"
#include "struct/ServerDeleteStruct.h"
#include "ImageWorker.h"

class ServerDBManager
{
public:
    explicit ServerDBManager();
    ~ServerDBManager();

    AddResult addServer(std::shared_ptr<DBConnection> connection_, const std::vector<uint8_t>& image_, const std::string& serverName_, const std::string& serverDescription_) const;
    std::vector<ServerStruct> getServers(std::shared_ptr<DBConnection> connection_, const int userID_);
    ServerDeleteStruct deleteServer(std::shared_ptr<DBConnection> connection_, const int serverId_) const;

private:
    ImageWorker imageWorker_;
};

#endif // SERVERDBMANAGER_H
