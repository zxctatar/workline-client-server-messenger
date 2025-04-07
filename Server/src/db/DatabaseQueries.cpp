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

pqxx::result DatabaseQueries::getUserServers(pqxx::transaction_base& conn_, const int userID_)
{
    return conn_.exec_params(R"(SELECT s.server_id, s.server_name, s.server_description FROM servers s
                     JOIN users_on_servers uos ON s.server_id = uos.server_id
                     WHERE uos.user_id = $1)", userID_);
}

pqxx::result DatabaseQueries::getAllServers(pqxx::transaction_base& conn_)
{
    return conn_.exec("SELECT server_id, server_name, server_description FROM servers");
}

pqxx::result DatabaseQueries::getUserData(pqxx::transaction_base& conn_, const std::string& login_)
{
    return conn_.exec_params("SELECT firstname, lastname, middlename, email, phone_number FROM users WHERE login = $1", login_);
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
    return conn_.exec(R"(SELECT user_id, firstname, lastname, middlename
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
    return conn_.exec_params(R"(SELECT user_id, firstname, lastname, middlename
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
        u.firstname,
        u.lastname,
        u.middlename,
        COALESCE(m.content, '') AS last_message,
        COALESCE(m.sent_at, '1970-01-01 00:00:00') AS last_message_time,
        COALESCE(p.id, 0) AS private_chat_id,
        CASE
            WHEN p.id IS NOT NULL THEN TRUE
            ELSE FALSE
        END AS has_chat
    FROM users u
    LEFT JOIN private_chats p
        ON (
            (p.user1_id = $1 AND p.user2_id = u.user_id) OR
            (p.user2_id = $1 AND p.user1_id = u.user_id)
        )
        AND p.server_id = $2
    LEFT JOIN LATERAL (
        SELECT content, sent_at
        FROM messages
        WHERE private_chat_id = p.id
        ORDER BY sent_at DESC
        LIMIT 1
    ) m ON TRUE
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
