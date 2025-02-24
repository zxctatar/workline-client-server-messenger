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
                break;
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

        pqxx::result result_check_admin_table_ = check_tables_.exec(R"(
            SELECT 1
            FROM information_schema.tables
            WHERE table_schema = 'public'
                AND table_name = 'admins'
            )");

        check_tables_.commit();

        if(result_check_users_table_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Users table not found. Creating users table...";

            pqxx::work create_users_table_(connection_to_worklinedatabase_);

            create_users_table_.exec(R"(
                CREATE TABLE users(
                    user_id SERIAL PRIMARY KEY,
                    firstname VARCHAR(50) NOT NULL,
                    lastname VARCHAR(50) NOT NULL,
                    middlename VARCHAR(50) NOT NULL,
                    login VARCHAR(50) NOT NULL,
                    email VARCHAR(100) NOT NULL,
                    phone_number BIGINT NOT NULL,
                    Registration_date TIMESTAMP,
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

        if(result_check_admin_table_.empty())
        {
            BOOST_LOG_TRIVIAL(info) << "Admin table not found. Creating users table...";

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

        for(const auto& row : result_check_privileges_)
        {
            const std::string privilege_ = row["privilege_type"].c_str();
            if(privilege_ == "SELECT") has_select_ = true;
            if(privilege_ == "INSERT") has_insert_ = true;
        }

        if(!has_select_)
        {
            BOOST_LOG_TRIVIAL(info) << "SELECT privilege does not exist. Setting privilege...";

            pqxx::nontransaction add_select_privilege_(connection_to_worklinedatabase_);
            add_select_privilege_.exec("GRANT SELECT ON ALL TABLES IN SCHEMA public TO wluser;");
            add_select_privilege_.exec("GRANT USAGE ON SEQUENCE users_user_id_seq TO wluser;");
            add_select_privilege_.commit();
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "SELECT privilege already set.";
        }

        if(!has_insert_)
        {
            BOOST_LOG_TRIVIAL(info) << "INSERT privilege does not exist. Setting privilege...";

            pqxx::nontransaction add_insert_privilege_(connection_to_worklinedatabase_);
            add_insert_privilege_.exec("GRANT INSERT ON ALL TABLES IN SCHEMA public TO wluser;");
            add_insert_privilege_.commit();
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "INSERT privilege already set.";
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

void Database::createTrigger(pqxx::connection& connection_to_worklinedatabase_)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Creating a trigger...";

        pqxx::work create_trigger(connection_to_worklinedatabase_);

        create_trigger.exec("DROP TRIGGER IF EXISTS trigger_set_verified ON admins;");
        create_trigger.exec("DROP FUNCTION IF EXISTS set_verified_on_admin_insert;");

        // SQL-команда для создания функции триггера
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

        // SQL-команда для создания триггера
        create_trigger.exec(R"(
            CREATE TRIGGER trigger_set_verified
            AFTER INSERT ON admins
            FOR EACH ROW
            EXECUTE FUNCTION set_verified_on_admin_insert();
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
            INSERT INTO users (firstname, lastname, middlename, login, email, phone_number, password, verified_user)
            VALUES ('Максим', 'Кнутов', 'Владимирович', 'zxctatar', 'maksimknutov80@gmail.com', 79333668855, '123123', FALSE);
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
