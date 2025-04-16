#ifndef DATABASEQUERIES_H
#define DATABASEQUERIES_H

#include <pqxx/pqxx>
#include <string>

class DatabaseQueries
{
public:
    static pqxx::result checkUserLogin(pqxx::transaction_base& conn_, const std::string& login_);
    static pqxx::result checkUserPhoneNumber(pqxx::transaction_base& conn_, const long long int phoneNumber_);
    static pqxx::result checkUserEmail(pqxx::transaction_base& conn_, const std::string& email_);
    static pqxx::result registrationUser(pqxx::transaction_base& conn_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& login_, const std::string& email_, const long long int phoneNumber_, const std::string& password_);
    static pqxx::result checkDataVerification(pqxx::transaction_base& conn_, const std::string& login_, const std::string& password_);
    static pqxx::result checkAccess(pqxx::transaction_base& conn_, const int userID_);
    static pqxx::result getUserId(pqxx::transaction_base& conn_, const std::string& login_);
    static pqxx::result checkIsAdmin(pqxx::transaction_base& conn_, const int userID_);
    static pqxx::result checkServerName(pqxx::transaction_base& conn_, const std::string& serverName_);
    static pqxx::result addNewServer(pqxx::transaction_base& conn_, const std::vector<uint8_t>& image_, const std::string& serverName_, const std::string& serverDescription_);
    static pqxx::result getUserServers(pqxx::transaction_base& conn_, const int userID_);
    static pqxx::result getAllServers(pqxx::transaction_base& conn_);
    static pqxx::result getUserData(pqxx::transaction_base& conn_, const std::string& login_);
    static pqxx::result deleteServer(pqxx::transaction_base& conn_, const int serverId_);
    static pqxx::result getUsersIdOnServers(pqxx::transaction_base& conn_, const int serverId_);
    static pqxx::result getUnverUsers(pqxx::transaction_base& conn_);
    static pqxx::result checkIfUserRejected(pqxx::transaction_base& conn_, const int userId_);
    static pqxx::result approveUser(pqxx::transaction_base& conn_, const int userId_);
    static pqxx::result rejectUser(pqxx::transaction_base& conn_, const int userId_);
    static pqxx::result getCandidateUsers(pqxx::transaction_base& conn_, const int serverId_);
    static pqxx::result checkUserOnServer(pqxx::transaction_base& conn_, const int userId_, const int serverId_);
    static pqxx::result addUserOnServer(pqxx::transaction_base& conn_, const int userId_, const int serverId_);
    static pqxx::result getChats(pqxx::transaction_base& conn_, const int userId_, const int serverId_);
    static pqxx::result createChat(pqxx::transaction_base& conn_, const int serverId_, const int userId_, const int companionId_);
    static pqxx::result getUsersOnServer(pqxx::transaction_base& conn_, const int serverId_);
    static pqxx::result checkUserOnAdmin(pqxx::transaction_base& conn_, const int serverId_, const int userId_);
    static pqxx::result addAdminOnServer(pqxx::transaction_base& conn_, const int serverId_, const int userId_);
    static pqxx::result removeAdminOnServer(pqxx::transaction_base& conn_, const int serverId_, const int userId_);
    static pqxx::result getServerRole(pqxx::transaction_base& conn_, const int serverId_, const int userId_);
    static pqxx::result checkChatAccess(pqxx::transaction_base& conn_, const int chatId_, const int userId_);
    static pqxx::result getChatHistory(pqxx::transaction_base& conn_, const int chatId_, const int userId_);
    static pqxx::result addMessage(pqxx::transaction_base& conn_, const int chatId_, const int userId_, const int serverId_, const std::string& message_);
};

#endif // DATABASEQUERIES_H
