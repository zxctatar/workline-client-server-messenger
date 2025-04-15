#include "../../../include/MessageDBManager.h"
#include "../../../include/DatabaseQueries.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>

MessageDBManager::MessageDBManager()
{
}

MessageDBManager::~MessageDBManager()
{
}


SetMessageResult MessageDBManager::setNewMessage(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_, const std::string& message_)
{
    SetMessageResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Adding a new message";

        if(!connection_->isConnected() || !connection_->isStarted())
        {
            BOOST_LOG_TRIVIAL(error) << "Сonnection problem.";
        }

        pqxx::work access_check_(connection_->getConnection());
        pqxx::result result_access_check_ = DatabaseQueries::checkAccess(access_check_, userId_);

        bool access_ = result_access_check_[0][0].as<bool>();

        access_check_.commit();

        if(access_)
        {
            pqxx::work check_chat_access_(connection_->getConnection());
            pqxx::result result_check_chat_access_ = DatabaseQueries::checkChatAccess(check_chat_access_, chatId_, userId_);
            check_chat_access_.commit();

            if(!result_check_chat_access_.empty())
            {
                pqxx::work add_message_(connection_->getConnection());
                pqxx::result result_add_message_ = DatabaseQueries::addMessage(add_message_, chatId_, userId_, serverId_, message_);
                add_message_.commit();

                result_.messageId_ = result_add_message_[0][0].as<int>();
                result_.message_ = result_add_message_[0][1].as<std::string>();
                result_.time_ = result_add_message_[0][2].as<std::string>();
                result_.companionId_ = result_add_message_[0][3].as<int>();

                return result_;
            }
            else
            {
                return SetMessageResult();
            }
        }
        else
        {
            return SetMessageResult();
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return SetMessageResult();
    }
}
