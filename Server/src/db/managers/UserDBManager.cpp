#include "../../../include/DatabaseQueries.h"
#include "../../../include/UserDBManager.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>

UserDBManager::UserDBManager()
{}

UserDBManager::~UserDBManager()
{}

std::string UserDBManager::regUser(std::shared_ptr<DBConnection> connection_, const std::vector<uint8_t>& image_, const std::string& lastName_, const std::string& firstName_, const std::string& middleName_, const std::string& birthDate_, const std::string& login_, const long long int phoneNumber_, const std::string& email_, const std::string& password_) const
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
            pqxx::result result_reg_user = DatabaseQueries::registrationUser(reg_user_, image_, firstName_, lastName_,
                                                                             middleName_, birthDate_, login_, email_,
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

                    if (!result_get_initials_[0][0].is_null())
                    {
                        pqxx::binarystring imageData_ = result_get_initials_[0][0].as<pqxx::binarystring>();
                        std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                        result_.userAvatar_ = imageWorker_.base64_encode(imageBytes_);
                    }
                    else
                    {
                        result_.userAvatar_ = "";
                    }

                    result_.userFirstName_ = result_get_initials_[0][1].as<std::string>();
                    result_.userLastName_ = result_get_initials_[0][2].as<std::string>();
                    result_.userMiddleName_ = result_get_initials_[0][3].is_null() ? "" : result_get_initials_[0][3].as<std::string>();
                    result_.userBirthDate_ = result_get_initials_[0][4].as<std::string>();
                    result_.userEmail_ = result_get_initials_[0][5].as<std::string>();
                    result_.userPhoneNumber = result_get_initials_[0][6].as<std::string>();
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

                if (!result_get_initials_[0][0].is_null())
                {
                    pqxx::binarystring imageData_ = result_get_initials_[0][0].as<pqxx::binarystring>();
                    std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                    result_.userAvatar_ = imageWorker_.base64_encode(imageBytes_);
                }
                else
                {
                    result_.userAvatar_ = "";
                }

                result_.userFirstName_ = result_get_initials_[0][1].as<std::string>();
                result_.userLastName_ = result_get_initials_[0][2].as<std::string>();
                result_.userMiddleName_ = result_get_initials_[0][3].is_null() ? "" : result_get_initials_[0][3].as<std::string>();
                result_.userBirthDate_ = result_get_initials_[0][4].as<std::string>();
                result_.userEmail_ = result_get_initials_[0][5].as<std::string>();
                result_.userPhoneNumber = result_get_initials_[0][6].as<std::string>();
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
            else if(!result_check_is_admin_.empty())
            {
                result_.userRole_ = "admin";
                return result_;
            }
            else
            {
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

            pqxx::binarystring imageData_ = row[1].as<pqxx::binarystring>();
            std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
            unverUser_.avatar_ = imageWorker_.base64_encode(imageBytes_);

            unverUser_.firstName_ = row[2].as<std::string>();
            unverUser_.lastName_ = row[3].as<std::string>();
            unverUser_.middleName_ = row[4].as<std::string>();

            unverUsers_.push_back(unverUser_);
        }

        BOOST_LOG_TRIVIAL(info) << "Unverified users have been received.";

        return unverUsers_;
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return std::vector<UnverUserStruct>();
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

            if(!row[1].is_null())
            {
                pqxx::binarystring imageData_ = row[1].as<pqxx::binarystring>();
                std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                candidateUser_.avatar_ = imageWorker_.base64_encode(imageBytes_);
            }
            else
            {
                candidateUser_.avatar_ = "";
            }

            candidateUser_.firstName_ = row[2].as<std::string>();
            candidateUser_.lastName_ = row[3].as<std::string>();
            candidateUser_.middleName_ = row[4].as<std::string>();

            candidateUsers_.push_back(candidateUser_);
        }

        BOOST_LOG_TRIVIAL(info) << "Candidate users have been received.";

        return candidateUsers_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return std::vector<CandidateUserStruct>();
    }
}

AddUserOnServerResult UserDBManager::addUserOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_)
{
    AddUserOnServerResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Add user on server...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_access_(connection_->getConnection());
        pqxx::result result_check_access_ = DatabaseQueries::checkAccess(check_access_, userId_);
        check_access_.commit();

        bool access_ = result_check_access_[0][0].as<bool>();

        if(access_)
        {
            pqxx::work check_if_added_(connection_->getConnection());
            pqxx::result result_check_if_added_ = DatabaseQueries::checkUserOnServer(check_if_added_, userId_, serverId_);
            check_if_added_.commit();

            if(result_check_if_added_.empty())
            {
                pqxx::work add_user_on_server_(connection_->getConnection());
                pqxx::result result_add_user_on_server_ = DatabaseQueries::addUserOnServer(add_user_on_server_, userId_, serverId_);
                add_user_on_server_.commit();

                BOOST_LOG_TRIVIAL(info) << "User added.";

                auto row = result_add_user_on_server_[0];
                result_.lastName_ = row[0].as<std::string>();
                result_.firstName_ = row[1].as<std::string>();
                result_.middleName_ = row[2].as<std::string>();

                if(!row[3].is_null())
                {
                    pqxx::binarystring imageData_ = row[3].as<pqxx::binarystring>();
                    std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                    result_.avatar_ = imageWorker_.base64_encode(imageBytes_);
                }
                else
                {
                    result_.serverImage_ = "";
                }

                if(!row[4].is_null())
                {
                    pqxx::binarystring imageData_ = row[4].as<pqxx::binarystring>();
                    std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                    result_.serverImage_ = imageWorker_.base64_encode(imageBytes_);
                }
                else
                {
                    result_.serverImage_ = "";
                }

                result_.serverName_ = row[5].as<std::string>();
                result_.serverDescription_ = row[6].as<std::string>();
                result_.code_ = "USER_ADDED";

                return result_;
            }
            else
            {
                result_.code_ = "ALREADY_ADDED";
                return result_;
            }
        }
        else
        {
            result_.code_ = "USER_NOT_VERIFIED";
            return result_;
        }
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        result_.code_ = "ERROR";
        return result_;
    }
}

std::vector<UsersOnServerStruct> UserDBManager::getUsersOnServer(std::shared_ptr<DBConnection> connection_, const int serverId_) const
{
    std::vector<UsersOnServerStruct> users_;
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get users on the server...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work get_users_(connection_->getConnection());
        pqxx::result result_get_users_ = DatabaseQueries::getUsersOnServer(get_users_, serverId_);
        get_users_.commit();

        for(const auto& row : result_get_users_)
        {
            UsersOnServerStruct user_;
            user_.userId_ = row[0].as<int>();

            if(!row[1].is_null())
            {
                pqxx::binarystring imageData_ = row[1].as<pqxx::binarystring>();
                std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                user_.avatar_ = imageWorker_.base64_encode(imageBytes_);
            }
            else
            {
                user_.avatar_ = "";
            }

            user_.firstName_ = row[2].as<std::string>();
            user_.lastName_ = row[3].as<std::string>();
            user_.middleName_ = row[4].as<std::string>();
            user_.isServerAdmin_ = row[5].as<bool>();
            user_.isGlobalAdmin_ = row[6].as<bool>();

            users_.push_back(user_);
        }

        BOOST_LOG_TRIVIAL(info) << "Users received.";

        return users_;
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();

        return std::vector<UsersOnServerStruct>();
    }
}

std::string UserDBManager::addAdminOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Set the user to the admin role...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_admin_(connection_->getConnection());
        pqxx::result result_check_admin_ = DatabaseQueries::checkUserOnAdmin(check_admin_, serverId_, userId_);
        check_admin_.commit();

        if(result_check_admin_.empty())
        {
            pqxx::work add_admin_(connection_->getConnection());
            pqxx::result result_add_admin_ = DatabaseQueries::addAdminOnServer(add_admin_, serverId_, userId_);
            add_admin_.commit();

            if(result_add_admin_.affected_rows() > 0)
            {
                BOOST_LOG_TRIVIAL(info) << "Admin role added.";
                return "ADMIN_ADDED";
            }
            else
            {
                return "ALREADY_ADMIN";
            }
        }
        else
        {
            return "ALREADY_ADMIN";
        }
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return "ERROR";
    }
}

std::string UserDBManager::removeAdminOnServer(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Remove the admin role from the user...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_admin_(connection_->getConnection());
        pqxx::result result_check_admin_ = DatabaseQueries::checkUserOnAdmin(check_admin_, serverId_, userId_);
        check_admin_.commit();

        if(!result_check_admin_.empty())
        {
            pqxx::work remove_admin_(connection_->getConnection());
            pqxx::result result_remove_admin_ = DatabaseQueries::removeAdminOnServer(remove_admin_, serverId_, userId_);
            remove_admin_.commit();

            if(result_remove_admin_.affected_rows() > 0)
            {
                BOOST_LOG_TRIVIAL(info) << "Admin role removed.";
                return "ADMIN_REMOVED";
            }
            else
            {
                return "USER_NOT_ADMIN";
            }
        }
        else
        {
            return "USER_NOT_ADMIN";
        }
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return "ERROR";
    }
}

std::string UserDBManager::getServerRole(std::shared_ptr<DBConnection> connection_, const int userId_, const int serverId_) const
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get the server role...";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Connection problem.";
        }

        pqxx::work check_user_on_server_(connection_->getConnection());
        pqxx::result result_check_user_on_server_ = DatabaseQueries::checkUserOnServer(check_user_on_server_, userId_, serverId_);
        check_user_on_server_.commit();

        if(!result_check_user_on_server_.empty())
        {
            pqxx::work get_server_role_(connection_->getConnection());
            pqxx::result result_get_server_role_ = DatabaseQueries::getServerRole(get_server_role_, serverId_, userId_);
            get_server_role_.commit();

            BOOST_LOG_TRIVIAL(info) << "Got the server role.";

            if(result_get_server_role_.empty())
            {
                return "IS_USER";
            }
            else
            {
                return "IS_ADMIN";
            }
        }
        else
        {
            return "ACCESS_DENIED";
        }
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return "ERROR";
    }
}
