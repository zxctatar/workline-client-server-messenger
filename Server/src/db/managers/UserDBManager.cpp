#include "../../../include/DatabaseQueries.h"
#include "../../../include/UserDBManager.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>

UserDBManager::UserDBManager()
{}

UserDBManager::~UserDBManager()
{}

std::string UserDBManager::regUser(std::shared_ptr<DBConnection> connection_, const std::string& lastName_, const std::string& firstName_, const std::string& middleName_, const std::string& login_, const long long int phoneNumber_, const std::string& email_, const std::string& password_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Adding a new user...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
            return "0";
        }

        pqxx::work check_user_(connection_->getConnection());
        pqxx::result result_check_login_ = DatabaseQueries::checkUserLogin(check_user_, login_);
        pqxx::result result_check_phone_number_ = DatabaseQueries::checkUserPhoneNumber(check_user_, phoneNumber_);
        pqxx::result result_check_email_ = DatabaseQueries::checkUserEmail(check_user_, email_);
        check_user_.commit();

        if(!result_check_login_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "A user with this login exists.";
            return "LOGIN_EXISTS";
        }
        else if(!result_check_phone_number_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "A user with this phone number exists.";
            return "PHONE_NUMBER_EXISTS";
        }
        else if(!result_check_email_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "A user with this email exists.";
            return "EMAIL_EXISTS";
        }
        else
        {
            pqxx::work reg_user_(connection_->getConnection());
            pqxx::result result_reg_user = DatabaseQueries::registrationUser(reg_user_, firstName_, lastName_,
                                                                             middleName_, login_, email_,
                                                                             phoneNumber_, password_);
            reg_user_.commit();

            BOOST_LOG_TRIVIAL(info) << "User Registration successful.";
            return "REG_OK";
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return "ERROR";
    }
}

LoginResult UserDBManager::loginUser(std::shared_ptr<DBConnection> connection_, const std::string& login_, const std::string& password_) const
{
    LoginResult result_;
    result_.userID_ = 0;
    result_.userRole_ = "none";

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Login data verification...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work data_verification_(connection_->getConnection());
        pqxx::result result_data_verification_ = DatabaseQueries::checkDataVerification(data_verification_, login_, password_);
        data_verification_.commit();

        if(result_data_verification_.empty())
        {
            result_.code_ = "INCORRECT_DATA";
            return result_;
        }
        else
        {
            pqxx::work get_user_id_(connection_->getConnection());
            pqxx::result result_get_user_id_ = DatabaseQueries::getUserId(get_user_id_, login_);

            const int userID_ = result_get_user_id_[0][0].as<int>();

            get_user_id_.commit();

            pqxx::work check_is_admin_(connection_->getConnection());
            pqxx::result result_check_is_admin_ = DatabaseQueries::checkIsAdmin(check_is_admin_, userID_);
            check_is_admin_.commit();

            if(result_check_is_admin_.empty())
            {
                pqxx::work access_check_(connection_->getConnection());
                pqxx::result result_access_check_ = DatabaseQueries::checkAccess(access_check_, userID_);

                bool access_ = result_access_check_[0][0].as<bool>();

                access_check_.commit();

                if(access_)
                {
                    result_.code_ = "ACCESS_ALLOWED_USER";
                    result_.userID_ = userID_;
                    result_.userRole_ = "user";
                    return result_;
                }
                else
                {
                    result_.code_ = "ACCESS_DENIED";
                    return result_;
                }
            }
            else
            {
                result_.code_ = "ACCESS_ALLOWED_ADMIN";
                result_.userID_ = userID_;
                result_.userRole_ = "admin";
                return result_;
            }
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        result_.code_ = "ERROR";

        return result_;
    }
}
