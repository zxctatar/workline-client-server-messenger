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

    static pqxx::result addNewServer(pqxx::transaction_base& conn_, const std::string& serverName_, const std::string& serverDescription_);

    static pqxx::result getUserServres(pqxx::transaction_base& conn_, const int userID_);

    static pqxx::result getAllServers(pqxx::transaction_base& conn_);

    static pqxx::result getUserData(pqxx::transaction_base& conn_, const std::string& login_);

};

#endif // DATABASEQUERIES_H
