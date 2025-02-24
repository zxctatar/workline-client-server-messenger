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

pqxx::result DatabaseQueries::checkAccess(pqxx::transaction_base& conn_, const std::string& login_, const std::string& password_)
{
    return conn_.exec_params("SELECT verified_user FROM users WHERE login = $1 AND password $2", login_, password_);
}
