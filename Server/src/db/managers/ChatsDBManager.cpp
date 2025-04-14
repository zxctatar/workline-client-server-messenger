#include "../../../include/ChatsDBManager.h"
#include "../../../include/DatabaseQueries.h"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <pqxx/pqxx>

ChatsDBManager::ChatsDBManager()
{
}

ChatsDBManager::~ChatsDBManager()
{
}

std::vector<PrivateChatStruct> ChatsDBManager::getPrivateChats(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_)
{
    std::vector<PrivateChatStruct> privateChats_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Receive chats...";

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
            pqxx::work get_chats_(connection_->getConnection());
            pqxx::result result_get_chats_ = DatabaseQueries::getChats(get_chats_, userId_, serverId_);

            for(const auto& row : result_get_chats_)
            {
                int companionId_ = row[0].as<int>();
                std::string firstName_ = row[1].as<std::string>();
                std::string lastName_ = row[2].as<std::string>();
                std::string middleName_ = row[3].as<std::string>();
                std::string lastMessage_ = row[4].as<std::string>();
                std::string messageTime_ = row[5].as<std::string>();
                int chatId_ = row[6].as<int>();
                bool hasChat_ = row[7].as<bool>();

                PrivateChatStruct chat_;
                chat_.chatId_ = chatId_;
                chat_.companionId_ = companionId_;
                chat_.lastMessage_ = lastMessage_;
                chat_.firstName_ = firstName_;
                chat_.lastName_ = lastName_;
                chat_.middleName_ = middleName_;
                chat_.messageTime_ = messageTime_;
                chat_.isChat_ = hasChat_;

                privateChats_.push_back(chat_);
            }
        }
        return privateChats_;
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << e.what();
        return std::vector<PrivateChatStruct>();
    }
}

int ChatsDBManager::createChat(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int companionId_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Create chat...";

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
            pqxx::work create_chat_(connection_->getConnection());
            pqxx::result result_create_chat_ = DatabaseQueries::createChat(create_chat_, serverId_, userId_, companionId_);
            create_chat_.commit();

            if(!result_create_chat_.empty())
            {
                int chatId_ = result_create_chat_[0][0].as<int>();
                create_chat_.commit();
                BOOST_LOG_TRIVIAL(info) << "Chat created.";
                return chatId_;
            }
            else
            {
                BOOST_LOG_TRIVIAL(info) << "Chat not created.";
                return -1;
            }
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << e.what();
        return -1;
    }
}

std::vector<ChatHistoryResult> ChatsDBManager::getChatHistory(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_)
{
    std::vector<ChatHistoryResult> history_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get chat history...";

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
                pqxx::work get_chat_history_(connection_->getConnection());
                pqxx::result result_get_chat_history_ = DatabaseQueries::getChatHistory(get_chat_history_, chatId_, userId_);
                get_chat_history_.commit();

                for(const auto& row : result_get_chat_history_)
                {
                    ChatHistoryResult messageH_;

                    std::string message_ = row[0].as<std::string>();
                    std::string time_ = row[1].as<std::string>();
                    bool isCandidate_ = row[2].as<bool>();

                    history_.push_back(messageH_);
                }

                return history_;
            }
            else
            {
                return std::vector<ChatHistoryResult>();
            }
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << e.what();
        return std::vector<ChatHistoryResult>();
    }
}
