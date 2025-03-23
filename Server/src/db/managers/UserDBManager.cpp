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
                    pqxx::work get_initials_(connection_->getConnection());
                    pqxx::result result_get_initials_ = DatabaseQueries::getUserData(get_initials_, login_);
                    get_initials_.commit();

                    result_.code_ = "ACCESS_ALLOWED_USER";
                    result_.userID_ = userID_;
                    result_.userRole_ = "user";
                    result_.userFirstName_ = result_get_initials_[0][0].as<std::string>();
                    result_.userLastName_ = result_get_initials_[0][1].as<std::string>();
                    result_.userMiddleName_ = result_get_initials_[0][2].is_null() ? "" : result_get_initials_[0][2].as<std::string>();
                    result_.userEmail_ = result_get_initials_[0][3].as<std::string>();
                    result_.userPhoneNumber = result_get_initials_[0][4].as<std::string>();
                    result_.userLogin_ = login_;
                    result_.userPassword_ = password_;
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
                pqxx::work get_initials_(connection_->getConnection());
                pqxx::result result_get_initials_ = DatabaseQueries::getUserData(get_initials_, login_);
                get_initials_.commit();

                result_.code_ = "ACCESS_ALLOWED_ADMIN";
                result_.userID_ = userID_;
                result_.userRole_ = "admin";
                result_.userFirstName_ = result_get_initials_[0][0].as<std::string>();
                result_.userLastName_ = result_get_initials_[0][1].as<std::string>();
                result_.userMiddleName_ = result_get_initials_[0][2].is_null() ? "" : result_get_initials_[0][2].as<std::string>();
                result_.userEmail_ = result_get_initials_[0][3].as<std::string>();
                result_.userPhoneNumber = result_get_initials_[0][4].as<std::string>();
                result_.userLogin_ = login_;
                result_.userPassword_ = password_;
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

ReconnectResult UserDBManager::reconnectUser(std::shared_ptr<DBConnection> connection_, const std::string& login_, const std::string& password_) const
{
    ReconnectResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "User verification for reconnection...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work data_verification_(connection_->getConnection());
        pqxx::result result_data_verification_ = DatabaseQueries::checkDataVerification(data_verification_, login_, password_);
        data_verification_.commit();

        if(result_data_verification_.empty())
        {
            BOOST_LOG_TRIVIAL(error) << "INCORRECT_DATA";
            result_.code_ = "INCORRECT_DATA";
            return result_;
        }
        else
        {
            pqxx::work get_user_id_(connection_->getConnection());
            pqxx::result result_get_user_id_ = DatabaseQueries::getUserId(get_user_id_, login_);

            const int userID_ = result_get_user_id_[0][0].as<int>();
            result_.userID_ = userID_;

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
                    result_.userRole_ = "user";
                    return result_;
                }
                else
                {
                    BOOST_LOG_TRIVIAL(error) << "ACCESS_DENIED";
                    result_.code_ = "ACCESS_DENIED";
                    return result_;
                }
            }
            else
            {
                // result_.userRole_ = "admin";
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

std::vector<int> UserDBManager::getUsersOnServers(std::shared_ptr<DBConnection> connection_, const int serverId_) const
{
    std::vector<int> usersOnServersId_;
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get users on servers id...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work get_users_id_(connection_->getConnection());
        pqxx::result result_get_users_id_ = DatabaseQueries::getUsersIdOnServers(get_users_id_, serverId_);
        get_users_id_.commit();

        for(const auto& row : result_get_users_id_)
        {
            int userId_ = row["user_id"].as<int>();
            usersOnServersId_.push_back(userId_);
        }

        return usersOnServersId_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return usersOnServersId_;
    }
}

std::vector<UnverUserStruct> UserDBManager::getUnverUsers(std::shared_ptr<DBConnection> connection_) const
{
    std::vector<UnverUserStruct> unverUsers_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get unverified users...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work get_unver_users_(connection_->getConnection());
        pqxx::result result_get_unver_users_ = DatabaseQueries::getUnverUsers(get_unver_users_);
        get_unver_users_.commit();

        for(const auto& row : result_get_unver_users_)
        {
            UnverUserStruct unverUser_;
            unverUser_.userId_ = row[0].as<int>();
            unverUser_.firstName_ = row[1].as<std::string>();
            unverUser_.lastName_ = row[2].as<std::string>();
            unverUser_.middleName_ = row[3].as<std::string>();

            unverUsers_.push_back(unverUser_);
        }

        BOOST_LOG_TRIVIAL(info) << "Unverified users have been received.";

        return unverUsers_;
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return unverUsers_;
    }
}

std::string UserDBManager::approveUser(std::shared_ptr<DBConnection> connection_, const int userId_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Trying to approve user...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_if_rejected_(connection_->getConnection());
        pqxx::result result_check_if_rejected_ = DatabaseQueries::checkIfUserRejected(check_if_rejected_, userId_);
        check_if_rejected_.commit();

        if(result_check_if_rejected_.empty())
        {
            pqxx::work check_access_(connection_->getConnection());
            pqxx::result result_check_access_ = DatabaseQueries::checkAccess(check_access_, userId_);

            bool access_ = result_check_access_[0][0].as<bool>();

            check_access_.commit();

            if(access_)
            {
                return "ALREADY_APPROVED";
            }
            else
            {
                pqxx::work approve_user_(connection_->getConnection());
                pqxx::result result_approve_user_ = DatabaseQueries::approveUser(approve_user_, userId_);
                approve_user_.commit();

                BOOST_LOG_TRIVIAL(info) << "User approved...";

                return "APPROVED";
            }
        }
        else
        {
            return "ALREADY_REJECTED";
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return "ERROR";
    }
}

std::string UserDBManager::rejectUser(std::shared_ptr<DBConnection> connection_, const int userId_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Trying to reject user...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_if_rejected_(connection_->getConnection());
        pqxx::result result_check_if_rejected_ = DatabaseQueries::checkIfUserRejected(check_if_rejected_, userId_);
        check_if_rejected_.commit();

        if(result_check_if_rejected_.empty())
        {
            pqxx::work check_access_(connection_->getConnection());
            pqxx::result result_check_access_ = DatabaseQueries::checkAccess(check_access_, userId_);

            bool access_ = result_check_access_[0][0].as<bool>();

            check_access_.commit();

            if(access_)
            {
                return "ALREADY_APPROVED";
            }
            else
            {
                pqxx::work reject_user_(connection_->getConnection());
                pqxx::result result_reject_user_ = DatabaseQueries::rejectUser(reject_user_, userId_);
                reject_user_.commit();

                BOOST_LOG_TRIVIAL(info) << "User rejected...";

                return "REJECTED";
            }
        }
        else
        {
            return "ALREADY_REJECTED";
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return "ERROR";
    }
}

std::vector<CandidateUserStruct> UserDBManager::getCandidateUsers(std::shared_ptr<DBConnection> connection_, const int serverId_) const
{
    std::vector<CandidateUserStruct> candidateUsers_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get candidate users...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work get_candidate_users_(connection_->getConnection());
        pqxx::result result_get_candidate_users_ = DatabaseQueries::getCandidateUsers(get_candidate_users_, serverId_);
        get_candidate_users_.commit();

        for(const auto& row : result_get_candidate_users_)
        {
            CandidateUserStruct candidateUser_;

            candidateUser_.userId_ = row[0].as<int>();
            candidateUser_.firstName_ = row[1].as<std::string>();
            candidateUser_.lastName_ = row[2].as<std::string>();
            candidateUser_.middleName_ = row[3].as<std::string>();

            candidateUsers_.push_back(candidateUser_);
        }

        BOOST_LOG_TRIVIAL(info) << "Candidate users have been received.";

        return candidateUsers_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return candidateUsers_;
    }
}
