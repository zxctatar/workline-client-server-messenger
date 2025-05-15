#include "../../include/Database.h"
#include <pqxx/pqxx>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

Database::Database(boost::asio::io_context& io_context, std::string& conninfo_to_postgres, std::string& conninfo_to_worklinedatabase)
    : io_context_(io_context)
    , conninfo_to_postgres_(conninfo_to_postgres)
    , conninfo_to_worklinedatabase_(conninfo_to_worklinedatabase)
{
    initializing();
}

void Database::initializing()
{
    int8_t stage_ = 0;

    DBConnection connection_to_postgres_(conninfo_to_postgres_);
    DBConnection connection_to_worklinedatabase_(conninfo_to_worklinedatabase_);

    while(true)
    {
        try
        {
            if(!connection_to_postgres_.isStarted())
            {
                BOOST_LOG_TRIVIAL(info) << "Connection to postgres...";
                connection_to_postgres_.connect();
            }

            switch (stage_)
            {
            case 0:
                createDatabase(connection_to_postgres_.getConnection());
                stage_++;
                // no break: intentionally falling through
            case 1:
                createUsers(connection_to_postgres_.getConnection());
                stage_++;
                connection_to_postgres_.stop();
                // no break: intentionally falling through
            case 2:
                if(!connection_to_worklinedatabase_.isStarted())
                {
                    BOOST_LOG_TRIVIAL(info) << "Connection to database...";
                    connection_to_worklinedatabase_.connect();
                }
                createTables(connection_to_worklinedatabase_.getConnection());
                stage_++;
                // no break: intentionally falling through
            case 3:
                setPrivileges(connection_to_worklinedatabase_.getConnection());
                stage_++;
                // no break: intentionally falling through
            case 4:
                createTrigger(connection_to_worklinedatabase_.getConnection());
                stage_++;
                //break;
                // no break: intentionally falling through
            case 5:
                insertAdmin(connection_to_worklinedatabase_.getConnection());
                stage_++;
                break;
            }
            break;
        }
        catch (const pqxx::broken_connection& e)
        {
            BOOST_LOG_TRIVIAL(error) << e.what();

            if(!connection_to_postgres_.isConnected() && connection_to_postgres_.isStarted())
            {
                connection_to_postgres_.reconnect();
                continue;
            }
            else if(!connection_to_worklinedatabase_.isConnected() && connection_to_worklinedatabase_.isStarted())
            {
                connection_to_worklinedatabase_.reconnect();
                continue;
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << "Unable to reconnect.";
                std::exit(EXIT_FAILURE);
            }
        }
        catch (const std::exception& e)
        {
            BOOST_LOG_TRIVIAL(error) << e.what();
            break;
        }
    }
}

void Database::createDatabase(pqxx::connection& connection_to_postgres_)
{
    try // подключение к postgres для проверки существует ли БД и если нет, то создать её
    {
        BOOST_LOG_TRIVIAL(info) << "Check if a database exists...";

        if(connection_to_postgres_.is_open())
        {
            pqxx::nontransaction check_db_(connection_to_postgres_);

            pqxx::result result_check_db_ = check_db_.exec("SELECT 1 FROM pg_database WHERE datname = 'worklinedatabase';");

            check_db_.commit();

            if(result_check_db_.empty())
            {
                BOOST_LOG_TRIVIAL(info) << "Database does not exist. Creating WorkLineDatabase...";

                pqxx::nontransaction create_db_(connection_to_postgres_);
                create_db_.exec("CREATE DATABASE worklinedatabase;");
                create_db_.commit();

                BOOST_LOG_TRIVIAL(info) << "Database created.";
            }
            else
            {
                BOOST_LOG_TRIVIAL(info) << "Database already exists.";
            }
        }
    }
    catch (const pqxx::broken_connection& e)
    {
        throw;
    }
    catch (const pqxx::sql_error& e)
    {
        BOOST_LOG_TRIVIAL(error) << "what: " << e.what() << ' ' << "query: " << e.query();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

void Database::createUsers(pqxx::connection& connection_to_postgres_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Check if user exists...";

        pqxx::nontransaction check_users_(connection_to_postgres_);
        pqxx::result result_check_user_ = check_users_.exec("SELECT 1 FROM pg_roles WHERE rolname = 'wluser';");
        check_users_.commit();

        if(result_check_user_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "User does not exist. Creating user role...";

            pqxx::nontransaction create_user_role_(connection_to_postgres_);
            create_user_role_.exec("CREATE USER wluser WITH PASSWORD 'FxNSpxeD' NOSUPERUSER NOCREATEDB NOCREATEROLE NOINHERIT LOGIN;");
            create_user_role_.commit();

            BOOST_LOG_TRIVIAL(info) << "User role created.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "User role already exists.";
        }
    }
    catch (const pqxx::broken_connection& e)
    {
        throw;
    }
    catch (const pqxx::sql_error& e)
    {
        BOOST_LOG_TRIVIAL(error) << "what: " << e.what() << ' ' << "query: " << e.query();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

void Database::createTables(pqxx::connection& connection_to_worklinedatabase_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Check if tables exists...";

        pqxx::nontransaction check_tables_(connection_to_worklinedatabase_);

        pqxx::result result_check_users_table_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'users'
            )");

        pqxx::result result_check_admins_table_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'admins'
            )");

        pqxx::result result_check_servers_table_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'servers'
            )");

        pqxx::result result_check_users_on_servers_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'users_on_servers'
            )");

        pqxx::result result_check_rejected_users_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'rejected_users'
            )");

        pqxx::result result_check_private_chats_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'private_chats'
            )");

        pqxx::result result_check_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'messages'
            )");

        pqxx::result result_check_admins_on_servers = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'admins_on_servers'
            )");

        pqxx::result result_check_chats_last_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'chats_last_messages'
            )");

        pqxx::result result_check_viewed_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'viewed_messages'
            )");

        pqxx::result result_check_group_chats_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'group_chats'
        )");

        pqxx::result result_check_group_chats_users_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'group_chats_users'
        )");

        pqxx::result result_check_group_chats_last_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'group_chats_last_messages'
        )");

        pqxx::result result_check_group_chats_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'group_chats_messages'
        )");

        pqxx::result result_check_group_chats_viewed_messages_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'group_chats_viewed_messages'
        )");

        check_tables_.commit();

        if(result_check_users_table_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Users table not found. Creating users table...";

            pqxx::work create_users_table_(connection_to_worklinedatabase_);

            create_users_table_.exec(R"(
                CREATE TABLE users(
                    user_id SERIAL PRIMARY KEY,
                    avatar BYTEA,
                    firstname VARCHAR(50) NOT NULL,
                    lastname VARCHAR(50) NOT NULL,
                    middlename VARCHAR(50) NOT NULL,
                    birth_date DATE NOT NULL,
                    login VARCHAR(50) NOT NULL,
                    email VARCHAR(100) NOT NULL,
                    phone_number BIGINT NOT NULL,
                    registration_date TIMESTAMP DEFAULT NOW(),
                    password VARCHAR(50) NOT NULL,
                    verified_user BOOLEAN NOT NULL DEFAULT FALSE
                    ))");

            create_users_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the users table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Users table already exists.";
        }

        if(result_check_admins_table_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Admin table not found. Creating admin table...";

            pqxx::work create_admin_table_(connection_to_worklinedatabase_);

            create_admin_table_.exec(R"(
                CREATE TABLE admins(
                    admin_id SERIAL PRIMARY KEY,
                    user_id INTEGER REFERENCES users(user_id) ON DELETE CASCADE
                    ))");

            create_admin_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the admin table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Admin table already exists.";
        }

        if(result_check_servers_table_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Server table not found. Creating server table...";

            pqxx::work create_server_table_(connection_to_worklinedatabase_);

            create_server_table_.exec(R"(
                CREATE TABLE servers(
                    server_id SERIAL PRIMARY KEY,
                    server_image BYTEA,
                    server_name VARCHAR(255) NOT NULL,
                    server_description VARCHAR(255)
                    ))");

            create_server_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the server table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Server table already exists.";
        }

        if(result_check_users_on_servers_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Users_on_servers table not found. Creating table...";

            pqxx::work create_users_on_servers_table_(connection_to_worklinedatabase_);

            create_users_on_servers_table_.exec(R"(
                CREATE TABLE users_on_servers(
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    server_id INTEGER NOT NULL REFERENCES servers(server_id) ON DELETE CASCADE,
                    UNIQUE (user_id, server_id)  -- Вот это гарантирует уникальность пары
                    ))");

            create_users_on_servers_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the users_on_servers table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Users_on_servers table already exists.";
        }

        if(result_check_rejected_users_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Rejected_users table not found. Creating table...";

            pqxx::work create_rejected_users_table_(connection_to_worklinedatabase_);

            create_rejected_users_table_.exec(R"(
                CREATE TABLE rejected_users(
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE
                    ))");

            create_rejected_users_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the rejected_users table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Rejected_users table already exists.";
        }

        if(result_check_private_chats_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Private_chats table not found. Creating table...";

            pqxx::work create_private_chats_table_(connection_to_worklinedatabase_);

            create_private_chats_table_.exec(R"(
                CREATE TABLE private_chats(
                    id SERIAL PRIMARY KEY,
                    server_id INTEGER NOT NULL REFERENCES servers(server_id) ON DELETE CASCADE,
                    user1_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    user2_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    CONSTRAINT unique_chat_per_server UNIQUE (server_id, user1_id, user2_id)
                    ))");

            create_private_chats_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the private_chats table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Private_chats table already exists.";
        }

        if(result_check_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Messages table not found. Creating table...";

            pqxx::work create_messages_table_(connection_to_worklinedatabase_);

            create_messages_table_.exec(R"(
                CREATE TABLE messages(
                    id SERIAL PRIMARY KEY,
                    sender_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    private_chat_id INTEGER NOT NULL REFERENCES private_chats(id) ON DELETE CASCADE,
                    content TEXT NOT NULL,
                    sent_at TIMESTAMP DEFAULT NOW()
                    ))");

            create_messages_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Messages table already exists.";
        }

        if(result_check_admins_on_servers.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Admins_on_servers table not found. Creating table...";

            pqxx::work create_admins_on_servers_table_(connection_to_worklinedatabase_);

            create_admins_on_servers_table_.exec(R"(
                CREATE TABLE admins_on_servers(
                    id SERIAL PRIMARY KEY,
                    server_id INTEGER NOT NULL REFERENCES servers(server_id) ON DELETE CASCADE,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE
                ))");

            create_admins_on_servers_table_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the admins_on_servers table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Admins_on_servers table already exists.";
        }

        if(result_check_chats_last_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Chats_last_messages table not found. Creating table...";

            pqxx::work create_chats_last_messages_(connection_to_worklinedatabase_);

            create_chats_last_messages_.exec(R"(
                CREATE TABLE chats_last_messages(
                    id SERIAL PRIMARY KEY,
                    chat_id INTEGER NOT NULL REFERENCES private_chats(id) ON DELETE CASCADE,
                    last_message_id INTEGER NOT NULL REFERENCES messages(id) ON DELETE CASCADE,
                    CONSTRAINT unique_chat_id UNIQUE (chat_id)
                ))");

            create_chats_last_messages_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the chats_last_messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Chats_last_messages table already exists.";
        }

        if(result_check_viewed_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Viewed_messages table not found. Creating table...";

            pqxx::work create_viewed_messages_(connection_to_worklinedatabase_);

            create_viewed_messages_.exec(R"(
                CREATE TABLE viewed_messages(
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    message_id INTEGER NOT NULL REFERENCES messages(id) ON DELETE CASCADE
                ))");

            create_viewed_messages_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the viewed_messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Viewed_messages table already exists.";
        }

        if(result_check_group_chats_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats table not found. Creating table...";

            pqxx::work create_group_chats_(connection_to_worklinedatabase_);

            create_group_chats_.exec(R"(
                CREATE TABLE group_chats(
                    id SERIAL PRIMARY KEY,
                    server_id INTEGER NOT NULL REFERENCES servers(server_id) ON DELETE CASCADE,
                    owner_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    group_name VARCHAR(255) NOT NULL,
                    group_avatar BYTEA
                ))");

            create_group_chats_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the group_chats table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats table already exists.";
        }

        if(result_check_group_chats_users_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chat_users table not found. Creating table...";

            pqxx::work create_group_chat_users_(connection_to_worklinedatabase_);

            create_group_chat_users_.exec(R"(
                CREATE TABLE group_chats_users(
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    group_chat_id INTEGER NOT NULL REFERENCES group_chats(id) ON DELETE CASCADE,
                    CONSTRAINT unique_user_in_group UNIQUE (user_id, group_chat_id)
                ))");

            create_group_chat_users_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the group_chat_users table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chat_users table already exists.";
        }

        if(result_check_group_chats_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats_messages table not found. Creating table...";

            pqxx::work create_group_chats_messages_(connection_to_worklinedatabase_);

            create_group_chats_messages_.exec(R"(
                CREATE TABLE group_chats_messages(
                    id SERIAL PRIMARY KEY,
                    sender_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    group_chat_id INTEGER NOT NULL REFERENCES group_chats(id) ON DELETE CASCADE,
                    content TEXT NOT NULL,
                    sent_at TIMESTAMP DEFAULT NOW()
                ))");

            create_group_chats_messages_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the group_chat_messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chat_messages table already exists.";
        }

        if(result_check_group_chats_last_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats_last_messages table not found. Creating table...";

            pqxx::work create_group_chats_last_messages_(connection_to_worklinedatabase_);

            create_group_chats_last_messages_.exec(R"(
                CREATE TABLE group_chats_last_messages(
                    id SERIAL PRIMARY KEY,
                    group_chat_id INTEGER NOT NULL REFERENCES group_chats(id) ON DELETE CASCADE,
                    last_message_id INTEGER NOT NULL REFERENCES group_chats_messages(id) ON DELETE CASCADE,
                    CONSTRAINT unique_group_chat_id UNIQUE (group_chat_id)
                ))");

            create_group_chats_last_messages_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the group_chats_last_messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats_last_messages table already exists.";
        }

        if(result_check_group_chats_viewed_messages_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats_viewed_messages table not found. Creating table...";

            pqxx::work create_group_chats_viewed_messages_(connection_to_worklinedatabase_);

            create_group_chats_viewed_messages_.exec(R"(
                CREATE TABLE group_chats_viewed_messages(
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER NOT NULL REFERENCES users(user_id) ON DELETE CASCADE,
                    message_id INTEGER NOT NULL REFERENCES group_chats_messages(id) ON DELETE CASCADE
                ))");

            create_group_chats_viewed_messages_.commit();

            BOOST_LOG_TRIVIAL(info) << "Creating the group_chats_viewed_messages table successfully.";
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "Group_chats_viewed_messages table already exists.";
        }
    }
    catch (const pqxx::broken_connection& e)
    {
        throw;
    }
    catch (const pqxx::sql_error& e)
    {
        BOOST_LOG_TRIVIAL(error) << "what: " << e.what() << ' ' << "query: " << e.query();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

void Database::setPrivileges(pqxx::connection& connection_to_worklinedatabase_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Checking if the user has rights...";

        // Проверка текущих прав пользователя
        pqxx::work check_user_roles_(connection_to_worklinedatabase_);

        pqxx::result result_check_privileges_ = check_user_roles_.exec(R"(
            SELECT privilege_type
            FROM information_schema.role_table_grants
            WHERE grantee = 'wluser'
              AND table_schema = 'public'
            )");

        check_user_roles_.commit();

        bool has_select_ = false;
        bool has_insert_ = false;
        bool has_update_ = false;
        bool has_delete_ = false;

        for(const auto& row : result_check_privileges_)
        {
            const std::string privilege_ = row["privilege_type"].c_str();
            if(privilege_ == "SELECT") has_select_ = true;
            if(privilege_ == "INSERT") has_insert_ = true;
            if(privilege_ == "UPDATE") has_update_ = true;
            if(privilege_ == "DELETE") has_delete_ = true;
        }

        // Предоставление прав, если они отсутствуют
        pqxx::nontransaction set_privileges_(connection_to_worklinedatabase_);

        if(!has_select_)
        {
            BOOST_LOG_TRIVIAL(info) << "SELECT privilege does not exist. Setting privilege...";
            set_privileges_.exec("GRANT SELECT ON ALL TABLES IN SCHEMA public TO wluser;");
        }

        if(!has_insert_)
        {
            BOOST_LOG_TRIVIAL(info) << "INSERT privilege does not exist. Setting privilege...";
            set_privileges_.exec("GRANT INSERT ON ALL TABLES IN SCHEMA public TO wluser;");
        }

        if(!has_update_)
        {
            BOOST_LOG_TRIVIAL(info) << "UPDATE privilege does not exist. Setting privilege...";
            set_privileges_.exec("GRANT UPDATE ON ALL TABLES IN SCHEMA public TO wluser;");
        }

        if(!has_delete_)
        {
            BOOST_LOG_TRIVIAL(info) << "DELETE privilege does not exist. Setting privilege...";
            set_privileges_.exec("GRANT DELETE ON ALL TABLES IN SCHEMA public TO wluser;");
        }

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE servers_server_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE users_user_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE rejected_users_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE users_on_servers_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE private_chats_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE admins_on_servers_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE messages_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE chats_last_messages_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE viewed_messages_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE group_chats_messages_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE group_chats_last_messages_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE group_chats_users_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE group_chats_id_seq TO wluser;");

        set_privileges_.exec("GRANT USAGE, SELECT ON SEQUENCE group_chats_viewed_messages_id_seq TO wluser;");

        set_privileges_.commit();

        BOOST_LOG_TRIVIAL(info) << "Privileges have been set successfully.";
    }
    catch (const pqxx::broken_connection& e)
    {
        throw;
    }
    catch (const pqxx::sql_error& e)
    {
        BOOST_LOG_TRIVIAL(error) << "what: " << e.what() << ' ' << "query: " << e.query();
    }
    catch (const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

void Database::createTrigger(pqxx::connection& connection_to_worklinedatabase_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Creating a trigger...";

        pqxx::work create_trigger(connection_to_worklinedatabase_);

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_set_verified ON admins;");
        create_trigger.exec("DROP FUNCTION IF EXISTS set_verified_on_admin_insert;");

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_set_verified_on_rejected ON rejected_users;");
        create_trigger.exec("DROP FUNCTION IF EXISTS set_verified_on_rejected_users_insert;");

        create_trigger.exec("DROP TRIGGER IF EXISTS update_trigger_set_verified ON users;");
        create_trigger.exec("DROP FUNCTION IF EXISTS user_verified_update;");

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_add_admins_to_new_server ON servers;");
        create_trigger.exec("DROP FUNCTION IF EXISTS add_admins_to_new_server;");

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_add_admin_to_all_servers ON admins;");
        create_trigger.exec("DROP FUNCTION IF EXISTS add_admin_to_all_servers;");

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_update_chats_last_messages_ ON messages;");
        create_trigger.exec("DROP FUNCTION IF EXISTS update_chats_last_messages_;");

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_update_group_chats_last_messages ON group_chats_messages;");
        create_trigger.exec("DROP FUNCTION IF EXISTS update_group_chats_last_messages;");

        // тригер обноваить verifed_user = true если стал админом
        create_trigger.exec(R"(
            CREATE OR REPLACE FUNCTION set_verified_on_admin_insert()
            RETURNS TRIGGER AS $$
            BEGIN
                UPDATE users
                SET verified_user = TRUE
                WHERE user_id = NEW.user_id;
                RETURN NEW;
            END;
            $$ LANGUAGE plpgsql;
        )");

        create_trigger.exec(R"(
            CREATE TRIGGER trigger_set_verified
            AFTER INSERT ON admins
            FOR EACH ROW
            EXECUTE FUNCTION set_verified_on_admin_insert();
        )");

        // обновить verified_user = false, если добавили в rejected_users
        create_trigger.exec(R"(
            CREATE OR REPLACE FUNCTION set_verified_on_rejected_users_insert()
            RETURNS TRIGGER AS $$
            BEGIN
                UPDATE users
                SET verified_user = FALSE
                WHERE user_id = NEW.user_id;
                RETURN NEW;
            END;
            $$ LANGUAGE plpgsql;
        )");

        create_trigger.exec(R"(
            CREATE TRIGGER trigger_set_verified_on_rejected
            AFTER INSERT ON rejected_users
            FOR EACH ROW
            EXECUTE FUNCTION set_verified_on_rejected_users_insert();
        )");

        // удаляем из rejected_users если verified_user стал true
        create_trigger.exec(R"(
    CREATE OR REPLACE FUNCTION user_verified_update()
    RETURNS TRIGGER AS $$
    BEGIN
        IF NEW.verified_user = true AND OLD.verified_user = false THEN
            DELETE FROM rejected_users
            WHERE user_id = NEW.user_id;
        END IF;

        RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
    )");

        create_trigger.exec(R"(
    CREATE TRIGGER update_trigger_set_verified
    AFTER UPDATE ON users
    FOR EACH ROW
    EXECUTE FUNCTION user_verified_update();
    )");

        // Функция для добавления всех администраторов на новый сервер
        create_trigger.exec(R"(
    CREATE OR REPLACE FUNCTION add_admins_to_new_server()
    RETURNS TRIGGER AS $$
    BEGIN
        INSERT INTO users_on_servers (user_id, server_id)
        SELECT a.user_id, NEW.server_id
        FROM admins a
        WHERE NOT EXISTS (
            SELECT 1
            FROM users_on_servers us
            WHERE us.user_id = a.user_id
            AND us.server_id = NEW.server_id
        );
        RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
    )");

        create_trigger.exec(R"(
    CREATE TRIGGER trigger_add_admins_to_new_server
    AFTER INSERT ON servers
    FOR EACH ROW
    EXECUTE FUNCTION add_admins_to_new_server();
    )");

        // Функция для добавления нового администратора на все серверы
        create_trigger.exec(R"(
    CREATE OR REPLACE FUNCTION add_admin_to_all_servers()
    RETURNS TRIGGER AS $$
    BEGIN
        INSERT INTO users_on_servers (user_id, server_id)
        SELECT NEW.user_id, s.server_id
        FROM servers s;
        RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
    )");

        create_trigger.exec(R"(
    CREATE TRIGGER trigger_add_admin_to_all_servers
    AFTER INSERT ON admins
    FOR EACH ROW
    EXECUTE FUNCTION add_admin_to_all_servers();
    )");

        // Функция для обновления или создание записи последнего сообщения в чате
        create_trigger.exec(R"(
    CREATE OR REPLACE FUNCTION update_chats_last_messages_()
    RETURNS TRIGGER AS $$
    BEGIN
        INSERT INTO chats_last_messages (chat_id, last_message_id)
        VALUES (NEW.private_chat_id, NEW.id)
        ON CONFLICT (chat_id)
        DO UPDATE SET last_message_id = EXCLUDED.last_message_id;

        RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
    )");

        create_trigger.exec(R"(
    CREATE TRIGGER trigger_update_chats_last_messages_
    AFTER INSERT ON messages
    FOR EACH ROW
    EXECUTE FUNCTION update_chats_last_messages_();
    )");

                // Функция для обновления записи последнего сообщения в групповом чате
                create_trigger.exec(R"(
    CREATE OR REPLACE FUNCTION update_group_chats_last_messages()
    RETURNS TRIGGER AS $$
    BEGIN
        -- Вставляем или обновляем запись в group_chats_last_messages
        INSERT INTO group_chats_last_messages (group_chat_id, last_message_id)
        VALUES (NEW.group_chat_id, NEW.id)
        ON CONFLICT (group_chat_id)
        DO UPDATE SET last_message_id = EXCLUDED.last_message_id;

        RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
            )");

        create_trigger.exec(R"(
    CREATE TRIGGER trigger_update_group_chats_last_messages
    AFTER INSERT ON group_chats_messages
    FOR EACH ROW
    EXECUTE FUNCTION update_group_chats_last_messages();
            )");

        create_trigger.commit();
        BOOST_LOG_TRIVIAL(info) << "Trigger created successfully.";
    }
    catch (const std::exception &e)
    {
        BOOST_LOG_TRIVIAL(error) << "Error creating trigger: " << e.what();
    }
}

void Database::insertAdmin(pqxx::connection& connection_to_worklinedatabase_)
{
    try
    {
        pqxx::work txn1(connection_to_worklinedatabase_);

        pqxx::result result = txn1.exec(R"(
            INSERT INTO users (firstname, lastname, middlename, birth_date, login, email, phone_number, password, verified_user)
            VALUES ('Максим', 'Кнутов', 'Владимирович', '18-03-2025', 'zxctatar', 'maksimknutov80@gmail.com', 79333668855, '123123', FALSE);
        )");

        txn1.commit();

        pqxx::work txn(connection_to_worklinedatabase_);

        txn.exec(R"(
            INSERT INTO admins (user_id) VALUES (1);
        )");

        txn.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating user: " << e.what() << std::endl;
    }
}

Database::~Database()
{}
