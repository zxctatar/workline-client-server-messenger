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

pqxx::result DatabaseQueries::registrationUser(pqxx::transaction_base& conn_, const std::vector<uint8_t>& image_, const std::string& firstName_, const std::string& lastName_, const std::string& middleName_, const std::string& birthDate_, const std::string& login_, const std::string& email_, const long long int phoneNumber_, const std::string& password_)
{
    pqxx::binarystring imageSQL_(image_.data(), image_.size());

    return conn_.exec_params(R"(
                INSERT INTO users(avatar, firstname, lastname, middlename, birth_date, login, email, phone_number, password, verified_user)
                VALUES($1,$2,$3,$4,$5,$6,$7,$8,$9, FALSE)
            )", imageSQL_, firstName_, lastName_, middleName_, birthDate_, login_, email_, phoneNumber_, password_);
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

pqxx::result DatabaseQueries::addNewServer(pqxx::transaction_base& conn_, const std::vector<uint8_t>& image_, const std::string& serverName_, const std::string& serverDescription_)
{
    pqxx::binarystring imageSQL_(image_.data(), image_.size());

    return conn_.exec_params(R"(INSERT INTO servers(server_image, server_name, server_description)
                             VALUES($1, $2, $3) RETURNING server_id)", imageSQL_, serverName_, serverDescription_);
}

pqxx::result DatabaseQueries::getUserServers(pqxx::transaction_base& conn_, const int userID_)
{
    return conn_.exec_params(R"(SELECT s.server_id, s.server_image, s.server_name, s.server_description FROM servers s
                     JOIN users_on_servers uos ON s.server_id = uos.server_id
                     WHERE uos.user_id = $1)", userID_);
}

pqxx::result DatabaseQueries::getAllServers(pqxx::transaction_base& conn_)
{
    return conn_.exec("SELECT server_id, server_image, server_name, server_description FROM servers");
}

pqxx::result DatabaseQueries::getUserData(pqxx::transaction_base& conn_, const std::string& login_)
{
    return conn_.exec_params("SELECT avatar, firstname, lastname, middlename, birth_date, email, phone_number FROM users WHERE login = $1", login_);
}

pqxx::result DatabaseQueries::deleteServer(pqxx::transaction_base& conn_, const int serverId_)
{
    return conn_.exec_params("DELETE FROM servers WHERE server_id = $1", serverId_);
}

pqxx::result DatabaseQueries::getUsersIdOnServers(pqxx::transaction_base& conn_, const int serverId_)
{
    return conn_.exec_params("SELECT user_id FROM users_on_servers WHERE server_id = $1", serverId_);
}

pqxx::result DatabaseQueries::getUnverUsers(pqxx::transaction_base& conn_)
{
    return conn_.exec(R"(SELECT user_id, avatar, firstname, lastname, middlename
                        FROM users
                        WHERE verified_user = false
                          AND NOT EXISTS (
                          SELECT 1
                          FROM rejected_users
                          WHERE rejected_users.user_id = users.user_id
                          ))");
}

pqxx::result DatabaseQueries::approveUser(pqxx::transaction_base& conn_, const int userId_)
{
    return conn_.exec_params("UPDATE users SET verified_user = true WHERE user_id = $1", userId_);
}

pqxx::result DatabaseQueries::rejectUser(pqxx::transaction_base& conn_, const int userId_)
{
    return conn_.exec_params("INSERT INTO rejected_users(user_id) VALUES($1)", userId_);
}

pqxx::result DatabaseQueries::checkIfUserRejected(pqxx::transaction_base& conn_, const int userId_)
{
    return conn_.exec_params("SELECT 1 FROM rejected_users WHERE user_id = $1", userId_);
}

pqxx::result DatabaseQueries::getCandidateUsers(pqxx::transaction_base& conn_, const int serverId_)
{
    return conn_.exec_params(R"(SELECT user_id, avatar, firstname, lastname, middlename
    FROM users
    WHERE verified_user = TRUE
    AND user_id NOT IN (SELECT user_id FROM users_on_servers WHERE server_id = $1)
    AND user_id NOT IN (SELECT user_id FROM admins)
    AND user_id NOT IN (SELECT user_id FROM rejected_users))", serverId_);
}

pqxx::result DatabaseQueries::checkUserOnServer(pqxx::transaction_base& conn_, const int userId_, const int serverId_)
{
    return conn_.exec_params("SELECT 1 FROM users_on_servers WHERE user_id = $1 AND server_id = $2", userId_, serverId_);
}

pqxx::result DatabaseQueries::addUserOnServer(pqxx::transaction_base& conn_, const int userId_, const int serverId_)
{
    return conn_.exec_params(R"(
        WITH ins AS (
            INSERT INTO users_on_servers(user_id, server_id)
            VALUES($1, $2)
            RETURNING user_id, server_id
        )
        SELECT
            u.lastname,
            u.firstname,
            u.middlename,
            u.avatar,
            s.server_image,
            s.server_name,
            s.server_description
        FROM ins
        JOIN users u ON u.user_id = ins.user_id
        JOIN servers s ON s.server_id = ins.server_id
    )", userId_, serverId_);
}

pqxx::result DatabaseQueries::getChats(pqxx::transaction_base& conn_, const int userId_, const int serverId_)
{
    return conn_.exec_params(R"(
    SELECT
        u.user_id AS user_id,
        u.avatar,
        u.firstname,
        u.lastname,
        u.middlename,
        COALESCE(m.content, '') AS last_message,
        COALESCE(m.sent_at, '1970-01-01 00:00:00') AS last_message_time,
        COALESCE(p.id, 0) AS private_chat_id,
        CASE
            WHEN p.id IS NOT NULL THEN TRUE
            ELSE FALSE
        END AS has_chat,
        COALESCE(unread.count, 0) AS unread_count
    FROM users u
    LEFT JOIN private_chats p
        ON (
            (p.user1_id = $1 AND p.user2_id = u.user_id) OR
            (p.user2_id = $1 AND p.user1_id = u.user_id)
        )
        AND p.server_id = $2
    LEFT JOIN chats_last_messages clm ON clm.chat_id = p.id
    LEFT JOIN messages m ON m.id = clm.last_message_id
    LEFT JOIN LATERAL (
        SELECT COUNT(*) AS count
        FROM messages msg
        WHERE msg.private_chat_id = p.id
          AND msg.sender_id != $1
          AND NOT EXISTS (
              SELECT 1 FROM viewed_messages vm
              WHERE vm.message_id = msg.id AND vm.user_id = $1
          )
    ) AS unread ON TRUE
    WHERE u.user_id != $1
    AND u.user_id IN (
        SELECT user_id FROM users_on_servers WHERE server_id = $2
    )
    ORDER BY u.firstname, u.lastname;)", userId_, serverId_);
}

pqxx::result DatabaseQueries::createChat(pqxx::transaction_base& conn_, const int serverId_, const int userId_, const int companionId_)
{
    return conn_.exec_params(R"( INSERT INTO private_chats(server_id, user1_id, user2_id)
                                 VALUES($1,$2,$3)
                                 RETURNING id)", serverId_, userId_, companionId_);
}

pqxx::result DatabaseQueries::getUsersOnServer(pqxx::transaction_base& conn_, const int serverId_)
{
    return conn_.exec_params(R"(
        SELECT
            u.user_id,
            u.avatar,
            u.firstname,
            u.lastname,
            u.middlename,
            CASE
                WHEN aos.user_id IS NOT NULL THEN TRUE
                ELSE FALSE
            END AS is_server_admin,
            CASE
                WHEN EXISTS (SELECT 1 FROM admins a WHERE a.user_id = u.user_id) THEN TRUE
                ELSE FALSE
            END AS is_global_admin
        FROM
            users_on_servers uos
        JOIN
            users u ON uos.user_id = u.user_id
        LEFT JOIN
            admins_on_servers aos ON uos.user_id = aos.user_id AND uos.server_id = aos.server_id
        WHERE
            uos.server_id = $1
        ORDER BY
            u.lastname, u.firstname;
    )", serverId_);
}

pqxx::result DatabaseQueries::checkUserOnAdmin(pqxx::transaction_base& conn_, const int serverId_, const int userId_)
{
    return conn_.exec_params("SELECT 1 FROM admins_on_servers WHERE server_id = $1 AND user_id = $2", serverId_, userId_);
}

pqxx::result DatabaseQueries::addAdminOnServer(pqxx::transaction_base& conn_, const int serverId_, const int userId_)
{
    return conn_.exec_params("INSERT INTO admins_on_servers(server_id, user_id) VALUES($1,$2)", serverId_, userId_);
}

pqxx::result DatabaseQueries::removeAdminOnServer(pqxx::transaction_base& conn_, const int serverId_, const int userId_)
{
    return conn_.exec_params("DELETE FROM admins_on_servers WHERE server_id = $1 AND user_id = $2", serverId_, userId_);
}

pqxx::result DatabaseQueries::getServerRole(pqxx::transaction_base& conn_, const int serverId_, const int userId_)
{
    return conn_.exec_params("SELECT 1 FROM admins_on_servers WHERE server_id = $1 AND user_id = $2", serverId_, userId_);
}

pqxx::result DatabaseQueries::checkChatAccess(pqxx::transaction_base& conn_, const int chatId_, const int userId_)
{
    return conn_.exec_params("SELECT 1 FROM private_chats WHERE id = $1 AND (user1_id = $2 OR user2_id = $2)", chatId_, userId_);
}

pqxx::result DatabaseQueries::getChatHistory(pqxx::transaction_base& conn_, const int chatId_, const int userId_)
{
    return conn_.exec_params(
        R"(
        SELECT
            m.id,
            m.content,
            m.sent_at,
            m.sender_id,
            m.sender_id <> $2 AS is_incoming,
            CASE
                WHEN m.sender_id = $2 THEN
                    EXISTS (
                        SELECT 1 FROM viewed_messages vm
                        WHERE vm.message_id = m.id AND vm.user_id = (
                            SELECT CASE
                                WHEN pc.user1_id = $2 THEN pc.user2_id
                                ELSE pc.user1_id
                            END
                            FROM private_chats pc
                            WHERE pc.id = m.private_chat_id
                        )
                    )
                ELSE
                    EXISTS (
                        SELECT 1 FROM viewed_messages vm
                        WHERE vm.message_id = m.id AND vm.user_id = $2
                    )
            END AS is_viewed
        FROM messages m
        WHERE m.private_chat_id = $1
        ORDER BY m.sent_at ASC
        )", chatId_, userId_);
}

pqxx::result DatabaseQueries::addMessage(pqxx::transaction_base& conn_, const int chatId_, const int userId_, const std::string& message_)
{
    return conn_.exec_params(
        R"(
            WITH inserted AS (
                INSERT INTO messages (sender_id, private_chat_id, content, sent_at)
                VALUES ($1, $2, $3, NOW())
                RETURNING id, content, sent_at
            )
            SELECT
                i.id,
                i.content,
                i.sent_at,
                CASE
                    WHEN pc.user1_id = $1 THEN pc.user2_id
                    ELSE pc.user1_id
                END AS companion_id
            FROM inserted i
            JOIN private_chats pc ON pc.id = $2
        )",
        userId_, chatId_, message_
        );
}

pqxx::result DatabaseQueries::getCompanionData(pqxx::transaction_base& conn_, const int chatId_, const int serverId_, const int userId_)
{
    return conn_.exec_params(R"(
        SELECT u.user_id, u.firstname, u.lastname, u.middlename, u.email, u.birth_date, u.phone_number
        FROM private_chats pc
        JOIN users u
            ON u.user_id = (
                CASE
                    WHEN pc.user1_id = $3 THEN pc.user2_id
                    ELSE pc.user1_id
                END
            )
        WHERE pc.server_id = $1 AND pc.id = $2
          AND ($3 = pc.user1_id OR $3 = pc.user2_id)
    )", serverId_, chatId_, userId_);
}

pqxx::result DatabaseQueries::addViewedMessage(pqxx::transaction_base& conn_, const int userId_, const int messageId_)
{
    return conn_.exec_params(R"(
        WITH inserted AS (
            INSERT INTO viewed_messages (user_id, message_id)
            VALUES ($1, $2)
            RETURNING message_id
        ),
        message_info AS (
            SELECT m.sender_id, m.private_chat_id
            FROM messages m
            WHERE m.id = $2
        ),
        chat_info AS (
            SELECT
                CASE
                    WHEN pc.user1_id = $1 THEN pc.user2_id
                    ELSE pc.user1_id
                END AS companion_id
            FROM private_chats pc
            JOIN message_info mi ON pc.id = mi.private_chat_id
        )
        SELECT * FROM chat_info;
    )", userId_, messageId_);
}

pqxx::result DatabaseQueries::checkGroupChatName(pqxx::transaction_base& conn_, const std::string& groupName_)
{
    return conn_.exec_params("SELECT 1 FROM group_chats WHERE group_name = $1", groupName_);
}

pqxx::result DatabaseQueries::createGroupChat(pqxx::transaction_base& conn_, const int userId_, const int serverId_, const std::string& groupName_, const std::vector<uint8_t>& groupAvatar_)
{
    pqxx::binarystring image_(groupAvatar_.data(), groupAvatar_.size());

    return conn_.exec_params(R"(
        INSERT INTO group_chats (server_id, owner_id, group_name, group_avatar)
        VALUES($1,$2,$3,$4)
        RETURNING id
    )", serverId_, userId_, groupName_, image_);
}

pqxx::result DatabaseQueries::addUserInGroup(pqxx::transaction_base& conn_, const int groupId_, const int userId_)
{
    return conn_.exec_params(R"(
        INSERT INTO group_chats_users (user_id, group_chat_id)
        VALUES ($1, $2)
        ON CONFLICT (user_id, group_chat_id) DO NOTHING
    )", userId_, groupId_);
}

pqxx::result DatabaseQueries::getGroupChats(pqxx::transaction_base& conn_, const int serverId_, const int userId_)
{
    return conn_.exec_params(R"(
        SELECT
            gc.id,
            gc.group_name,
            gc.group_avatar,
            m.content AS last_message_content,
            m.sent_at AS last_message_time,
            COALESCE((
                SELECT COUNT(*)
                FROM group_chats_messages gm
                WHERE gm.group_chat_id = gc.id
                AND gm.sender_id != $2
                AND NOT EXISTS (
                    SELECT 1
                    FROM group_chats_viewed_messages vm
                    WHERE vm.message_id = gm.id
                    AND vm.user_id = $2
                )
            ), 0) AS unread_count
        FROM
            group_chats gc
        JOIN
            group_chats_users gcu ON gc.id = gcu.group_chat_id AND gcu.user_id = $2
        LEFT JOIN
            group_chats_last_messages lm ON gc.id = lm.group_chat_id
        LEFT JOIN
            group_chats_messages m ON lm.last_message_id = m.id
        WHERE
            gc.server_id = $1
        ORDER BY
            COALESCE(m.sent_at) DESC
    )", serverId_, userId_);
}

pqxx::result DatabaseQueries::checkGroupChatAccess(pqxx::transaction_base& conn_, const int chatId_, const int userId_)
{
    return conn_.exec_params(R"(SELECT 1 FROM group_chats_users WHERE group_chat_id = $1 AND user_id = $2)", chatId_, userId_);
}

pqxx::result DatabaseQueries::getGroupChatHistory(pqxx::transaction_base& conn_, const int chatId_, const int userId_)
{
    return conn_.exec_params(
        R"(
        SELECT
            gm.id,
            gm.content,
            gm.sent_at,
            gm.sender_id,
            gm.sender_id <> $2 AS is_incoming,
            CASE
                WHEN gm.sender_id = $2 THEN
                    EXISTS (
                        SELECT 1
                        FROM group_chats_viewed_messages gvm
                        WHERE gvm.message_id = gm.id AND gvm.user_id != $2
                    )
                ELSE
                    EXISTS (
                        SELECT 1
                        FROM group_chats_viewed_messages gvm
                        WHERE gvm.message_id = gm.id AND gvm.user_id = $2
                    )
            END AS is_viewed
        FROM group_chats_messages gm
        WHERE gm.group_chat_id = $1
        ORDER BY gm.sent_at ASC
        )", chatId_, userId_);
}

pqxx::result DatabaseQueries::getGroupChatData(pqxx::transaction_base& conn_, const int serverId_, const int chatId_)
{
    return conn_.exec_params(
        R"(
        SELECT
            gc.group_name AS chat_name,
            (SELECT COUNT(*)
             FROM group_chats_users gcu
             WHERE gcu.group_chat_id = $2) AS members_count
        FROM group_chats gc
        WHERE gc.server_id = $1 AND gc.id = $2
        )", serverId_, chatId_);
}

pqxx::result DatabaseQueries::addGroupMessage(pqxx::transaction_base& conn_, const int chatId_, const int userId_, const std::string& message_)
{
    return conn_.exec_params(
        R"(
        WITH inserted AS (
            INSERT INTO group_chats_messages (sender_id, group_chat_id, content, sent_at)
            VALUES ($1, $2, $3, NOW())
            RETURNING id, content, sent_at
            )
        SELECT
            i.id,
            i.content,
            i.sent_at,
            ARRAY(
                SELECT gcu.user_id
                FROM group_chats_users gcu
                WHERE gcu.group_chat_id = $2
            ) AS companion_ids
        FROM inserted i;
        )", userId_, chatId_, message_);
}

pqxx::result DatabaseQueries::addViewedGroupMessage(pqxx::transaction_base& conn_, const int userId_, const int messageId_)
{
    return conn_.exec_params(R"(
        WITH inserted AS (
            INSERT INTO group_chats_viewed_messages (user_id, message_id)
            VALUES ($1, $2)
            ON CONFLICT DO NOTHING
            RETURNING message_id
        ),
        sender_info AS (
            SELECT gcm.sender_id
            FROM group_chats_messages gcm
            WHERE gcm.id = $2
            AND gcm.sender_id != $1
        )
        SELECT * FROM sender_info;
    )", userId_, messageId_);
}
