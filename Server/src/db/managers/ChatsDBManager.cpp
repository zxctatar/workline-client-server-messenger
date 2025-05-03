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

                std::string image_;

                if(!row[1].is_null())
                {
                    pqxx::binarystring imageData_ = row[1].as<pqxx::binarystring>();
                    std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                    image_ = imageWorker_.base64_encode(imageBytes_);
                }
                else
                {
                    image_ = "";
                }

                std::string firstName_ = row[2].as<std::string>();
                std::string lastName_ = row[3].as<std::string>();
                std::string middleName_ = row[4].as<std::string>();
                std::string lastMessage_ = row[5].as<std::string>();
                std::string messageTime_ = row[6].as<std::string>();
                int chatId_ = row[7].as<int>();
                bool hasChat_ = row[8].as<bool>();
                int newMessagesCount_ = row[9].as<int>();

                PrivateChatStruct chat_;
                chat_.chatId_ = chatId_;
                chat_.companionId_ = companionId_;
                chat_.avatar_ = image_;
                chat_.lastMessage_ = lastMessage_;
                chat_.firstName_ = firstName_;
                chat_.lastName_ = lastName_;
                chat_.middleName_ = middleName_;
                chat_.messageTime_ = messageTime_;
                chat_.isChat_ = hasChat_;
                chat_.newMessagesCount_ = newMessagesCount_;

                privateChats_.push_back(chat_);
            }
            return privateChats_;
        }
        return std::vector<PrivateChatStruct>();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
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
        else
        {
            return -1;
        }
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return -1;
    }
}

std::vector<ChatHistoryResult> ChatsDBManager::getChatHistory(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_, const bool isGroup_)
{
    std::vector<ChatHistoryResult> messages_;

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
            if(isGroup_)
            {
                pqxx::work check_group_chat_access_(connection_->getConnection());
                pqxx::result result_check_group_chat_access_ = DatabaseQueries::checkGroupChatAccess(check_group_chat_access_, chatId_, userId_);
                check_group_chat_access_.commit();

                if(!result_check_group_chat_access_.empty())
                {
                    pqxx::work get_group_chat_history_(connection_->getConnection());
                    pqxx::result result_get_group_chat_history_ = DatabaseQueries::getGroupChatHistory(get_group_chat_history_, chatId_, userId_);
                    get_group_chat_history_.commit();

                    for(const auto& row : result_get_group_chat_history_)
                    {
                        ChatHistoryResult messageH_;

                        messageH_.messageId_ = row[0].as<int>();
                        messageH_.message_ = row[1].as<std::string>();
                        messageH_.time_ = row[2].as<std::string>();
                        messageH_.senderId_ = row[3].as<int>();
                        messageH_.isCompanion_ = row[4].as<bool>();
                        messageH_.viewed_ = row[5].as<bool>();

                        messages_.push_back(messageH_);
                    }

                    return messages_;
                }
                else
                {
                    return std::vector<ChatHistoryResult>();
                }
            }
            else
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

                        messageH_.messageId_ = row[0].as<int>();
                        messageH_.message_ = row[1].as<std::string>();
                        messageH_.time_ = row[2].as<std::string>();
                        messageH_.senderId_ = row[3].as<int>();
                        messageH_.isCompanion_ = row[4].as<bool>();
                        messageH_.viewed_ = row[5].as<bool>();

                        messages_.push_back(messageH_);
                    }

                    return messages_;
                }
                else
                {
                    return std::vector<ChatHistoryResult>();
                }
            }
        }
        else
        {
            return std::vector<ChatHistoryResult>();
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return std::vector<ChatHistoryResult>();
    }
}

ChatDataResult ChatsDBManager::getChatData(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_,  const int chatId_)
{
    ChatDataResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get chat data...";

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
                pqxx::work get_chat_data_(connection_->getConnection());
                pqxx::result result_get_chat_data_ = DatabaseQueries::getCompanionData(get_chat_data_, chatId_, serverId_, userId_);
                get_chat_data_.commit();

                result_.userId_ = result_get_chat_data_[0][0].as<int>();
                result_.firstName_ = result_get_chat_data_[0][1].as<std::string>();
                result_.lastName_ = result_get_chat_data_[0][2].as<std::string>();
                result_.middleName_ = result_get_chat_data_[0][3].as<std::string>();
                result_.email_ = result_get_chat_data_[0][4].as<std::string>();
                result_.birthDate_ = result_get_chat_data_[0][5].as<std::string>();
                result_.phoneNumber_ = result_get_chat_data_[0][6].as<std::string>();

                return result_;
            }
            else
            {
                return result_;
            }
        }
        else
        {
            return result_;
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        return result_;
    }
}

CreateGroupChatResult ChatsDBManager::createGroupChat(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const std::string& groupName_, const std::vector<uint8_t>& groupAvatar_, const std::vector<int>& addedUsers_)
{
    CreateGroupChatResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Creating group chat...";

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
            pqxx::work check_group_chat_name_(connection_->getConnection());
            pqxx::result result_check_group_chat_name_ = DatabaseQueries::checkGroupChatName(check_group_chat_name_, groupName_);
            check_group_chat_name_.commit();

            if(result_check_group_chat_name_.empty())
            {
                pqxx::work create_group_chat_(connection_->getConnection());
                pqxx::result result_create_group_chat_ = DatabaseQueries::createGroupChat(create_group_chat_, userId_, serverId_, groupName_, groupAvatar_);
                create_group_chat_.commit();

                if(result_create_group_chat_.empty())
                {
                    result_.code_ = "ERROR";
                    return result_;
                }

                const int groupId_ = result_create_group_chat_[0][0].as<int>();
                result_.groupId_ = groupId_;

                pqxx::work add_user_in_group_(connection_->getConnection());
                pqxx::result result_add_user_in_group;

                for(const auto& userId_ : addedUsers_)
                {
                    result_add_user_in_group = DatabaseQueries::addUserInGroup(add_user_in_group_, groupId_, userId_);
                }

                add_user_in_group_.commit();

                result_.code_ = "ADD_NEW_GROUP_CHAT";
                return result_;
            }
            else
            {
                result_.code_ = "GROUP_NAME_EXISTS";
                return result_;
            }
        }
        else
        {
            result_.code_ = "ACCESS_DENIED";
            return result_;
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
        result_.code_ = "ERROR";
        return result_;
    }
}

std::vector<GroupChatStruct> ChatsDBManager::getGroupChats(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_)
{
    std::vector<GroupChatStruct> groupChats_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Receive group chats...";

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
            pqxx::result result_get_chats_ = DatabaseQueries::getGroupChats(get_chats_, serverId_, userId_);
            get_chats_.commit();

            for(const auto& row : result_get_chats_)
            {
                int chatId_ = row[0].as<int>();
                std::string chatName_ = row[1].as<std::string>();

                std::string image_;

                if(!row[2].is_null())
                {
                    pqxx::binarystring imageData_ = row[2].as<pqxx::binarystring>();
                    std::vector<uint8_t> imageBytes_(imageData_.begin(), imageData_.end());
                    image_ = imageWorker_.base64_encode(imageBytes_);
                }
                else
                {
                    image_ = "";
                }

                std::string lastMessage_;

                if(!row[3].is_null())
                {
                    lastMessage_ = row[3].as<std::string>();
                }
                else
                {
                    lastMessage_ = "";
                }

                std::string messageTime_;

                if(!row[4].is_null())
                {
                    messageTime_ = row[4].as<std::string>();
                }
                else
                {
                    messageTime_ = "";
                }

                int newMessagesCount_ = row[5].as<int>();

                GroupChatStruct groupChat_;
                groupChat_.chatId_ = chatId_;
                groupChat_.chatName_ = chatName_;
                groupChat_.avatar_ = image_;
                groupChat_.lastMessage_ = lastMessage_;
                groupChat_.messageTime_ = messageTime_;
                groupChat_.newMessagesCount_ = newMessagesCount_;

                groupChats_.push_back(groupChat_);
            }

            return groupChats_;
        }
        else
        {
            return std::vector<GroupChatStruct>();
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << e.what();
        return std::vector<GroupChatStruct>();
    }
}

GroupChatDataResult ChatsDBManager::getGroupChatData(std::shared_ptr<DBConnection> connection_, const int serverId_, const int userId_, const int chatId_)
{
    GroupChatDataResult result_;

    try
    {
        BOOST_LOG_TRIVIAL(info) << "Get chat data...";

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
            pqxx::work check_group_chat_access_(connection_->getConnection());
            pqxx::result result_check_group_chat_access_ = DatabaseQueries::checkGroupChatAccess(check_group_chat_access_, chatId_, userId_);
            check_group_chat_access_.commit();

            if(!result_check_group_chat_access_.empty())
            {
                pqxx::work get_group_chat_data_(connection_->getConnection());
                pqxx::result result_get_chat_data_ = DatabaseQueries::getGroupChatData(get_group_chat_data_, serverId_, chatId_);
                get_group_chat_data_.commit();

                result_.groupName_ = result_get_chat_data_[0][0].as<std::string>();
                result_.usersCount_ = result_get_chat_data_[0][1].as<int>();

                return result_;
            }
            else
            {
                return GroupChatDataResult();
            }
        }
        else
        {
            return GroupChatDataResult();
        }
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << e.what();
        return GroupChatDataResult();
    }
}
