#include "../../include/DatabaseQueries.h"

pqxx::result DatabaseQueries::checkUserLogin(pqxx::transaction_base& conn_, const std::string& login_)
{
    return conn_.exec_params("SELECT 1 FROM users WHERE login = $1", login_);
}

pqxx::result DatabaseQueries::checkUserPhoneNumber(pqxx::transaction_base& conn_, const long long int phoneNumber_)
{
    return conn_.exec_params("SELECT 1 FROM users WHERE phone_number = $1", phoneNumber_);
}

pqxx::result DatabaseQueries::checkUserEmail(pqxx::transaction_base& conn_, const std::string& email_)
{
    return conn_.exec_params("SELECT 1 FROM users WHERE email = $1", email_);
}

pqxx::result DatabaseQueries::registrationUser(pqxx::transaction_base& conn_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& login_, const std::string& email_, const long long int phoneNumber_, const std::string& password_)
{
    return conn_.exec_params(R"(
                INSERT INTO users(firstname, lastname, middlename, login, email, phone_number, password, verified_user)
                VALUES($1,$2,$3,$4,$5,$6,$7, FALSE)
            )", firstName_, lastName_, middleName_, login_, email_, phoneNumber_, password_);
}

pqxx::result DatabaseQueries::checkDataVerification(pqxx::transaction_base& conn_, const std::string& login_, const std::string& password_)
{
    return conn_.exec_params("SELECT 1 FROM users WHERE login = $1 AND password = $2", login_, password_);
}

pqxx::result DatabaseQueries::checkAccess(pqxx::transaction_base& conn_, const int userID_)
{
    return conn_.exec_params("SELECT verified_user FROM users WHERE user_id = $1", userID_);
}

pqxx::result DatabaseQueries::getUserId(pqxx::transaction_base& conn_, const std::string& login_)
{
    return conn_.exec_params("SELECT user_id FROM users WHERE login = $1", login_);
}

pqxx::result DatabaseQueries::checkIsAdmin(pqxx::transaction_base& conn_, const int userID_)
{
    return conn_.exec_params("SELECT 1 FROM admins WHERE user_id = $1", userID_);
}

pqxx::result DatabaseQueries::checkServerName(pqxx::transaction_base& conn_, const std::string& serverName_)
{
    return conn_.exec_params("SELECT 1 FROM servers WHERE server_name = $1", serverName_);
}

pqxx::result DatabaseQueries::addNewServer(pqxx::transaction_base& conn_, const std::string& serverName_, const std::string& serverDescription_)
{
    return conn_.exec_params(R"(INSERT INTO servers(server_name, server_description)
                             VALUES($1, $2) RETURNING server_id)", serverName_, serverDescription_);
}

pqxx::result DatabaseQueries::getUserServres(pqxx::transaction_base& conn_, const int userID_)
{
    return conn_.exec_params(R"(SELECT s.server_id, s.server_name FROM servers s
                     JOIN users_on_servers uos ON s.server_id = uos.server_id
                     WHERE uos.user_id = $1)", userID_);
}

pqxx::result DatabaseQueries::getAllServers(pqxx::transaction_base& conn_)
{
    return conn_.exec_params(R"(SELECT server_id, server_name, server_description FROM servers)");
}

pqxx::result DatabaseQueries::getUserData(pqxx::transaction_base& conn_, const std::string& login_)
{
    return conn_.exec_params(R"(SELECT firstname, lastname, middlename, email, phone_number FROM users WHERE login = $1)", login_);
}
