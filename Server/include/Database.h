#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

class Database
{
public:
    explicit Database(const std::string& connection_conf);

    ~Database();

private:
    void checkDatabase();
    void createDatabase();
    void createTables();
    void createUsers();
    void setPrivileges();

    const std::string connection_conf_;
};

#endif // DATABASE_H
