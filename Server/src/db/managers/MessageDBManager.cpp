#include "../../../include/MessageDBManager.h"
#include "../../../include/DatabaseQueries.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>
#include <iostream>

MessageDBManager::MessageDBManager()
{
}

MessageDBManager::~MessageDBManager()
{
}


SetMessageResult MessageDBManager::setNewMessage(std::shared_ptr<DBConnection> connection_, const int userId_, const int chatId_, const std::string& message_, const bool isGroup_)
{
    SetMessageResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Adding a new message...";

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
            if(isGroup_)
            {
                pqxx::work check_group_chat_access_(connection_->getConnection());
                pqxx::result result_check_group_chat_access_ = DatabaseQueries::checkGroupChatAccess(check_group_chat_access_, chatId_, userId_);
                check_group_chat_access_.commit();

                if(!result_check_group_chat_access_.empty())
                {
                    pqxx::work add_group_message_(connection_->getConnection());
                    pqxx::result result_add_group_message_ = DatabaseQueries::addGroupMessage(add_group_message_, chatId_, userId_, message_);
                    add_group_message_.commit();

                    result_.messageId_ = result_add_group_message_[0][0].as<int>();
                    result_.message_ = result_add_group_message_[0][1].as<std::string>();
                    result_.time_ = result_add_group_message_[0][2].as<std::string>();

                    pqxx::array_parser parser_ = result_add_group_message_[0][3].as_array();

                    while(true)
                    {
                        auto elem = parser_.get_next();
                        if (elem.first == pqxx::array_parser::juncture::done) {
                            break;
                        }
                        if (elem.first == pqxx::array_parser::juncture::string_value) {
                            result_.companions_.push_back(std::stoi(elem.second));
                        }
                    }

                    return result_;
                }
                else
                {
                    return SetMessageResult();
                }
            }
            else
            {
                pqxx::work check_chat_access_(connection_->getConnection());
                pqxx::result result_check_chat_access_ = DatabaseQueries::checkChatAccess(check_chat_access_, chatId_, userId_);
                check_chat_access_.commit();

                if(!result_check_chat_access_.empty())
                {
                    pqxx::work add_message_(connection_->getConnection());
                    pqxx::result result_add_message_ = DatabaseQueries::addMessage(add_message_, chatId_, userId_, message_);
                    add_message_.commit();

                    result_.messageId_ = result_add_message_[0][0].as<int>();
                    result_.message_ = result_add_message_[0][1].as<std::string>();
                    result_.time_ = result_add_message_[0][2].as<std::string>();
                    result_.companions_.push_back(result_add_message_[0][3].as<int>());

                    return result_;
                }
                else
                {
                    return SetMessageResult();
                }
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

int MessageDBManager::markMessage(std::shared_ptr<DBConnection> connection_, const int userId_, const int chatId_, const int messageId_, const bool isGroup_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Mark message...";

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
            if(isGroup_)
            {
                pqxx::work check_group_chat_access_(connection_->getConnection());
                pqxx::result result_check_group_chat_access_ = DatabaseQueries::checkGroupChatAccess(check_group_chat_access_, chatId_, userId_);
                check_group_chat_access_.commit();

                if(!result_check_group_chat_access_.empty())
                {
                    pqxx::work mark_group_message_(connection_->getConnection());
                    pqxx::result result_mark_group_message_ = DatabaseQueries::addViewedGroupMessage(mark_group_message_, userId_, messageId_);
                    mark_group_message_.commit();

                    return result_mark_group_message_[0][0].as<int>();
                }
                else
                {
                    return int();
                }
            }
            else
            {
                pqxx::work check_chat_access_(connection_->getConnection());
                pqxx::result result_check_chat_access_ = DatabaseQueries::checkChatAccess(check_chat_access_, chatId_, userId_);
                check_chat_access_.commit();

                if(!result_check_chat_access_.empty())
                {
                    pqxx::work mark_message_(connection_->getConnection());
                    pqxx::result result_mark_message_ = DatabaseQueries::addViewedMessage(mark_message_, userId_, messageId_);
                    mark_message_.commit();

                    return result_mark_message_[0][0].as<int>();
                }
                else
                {
                    return int();
                }
            }

        }
        else
        {
            return int();
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return int();
    }
}
