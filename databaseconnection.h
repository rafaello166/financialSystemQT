#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

class databaseConnection
{
public:
    databaseConnection();
    bool createUser(QString first_name, QString last_name, QString username, QString password);
    std::string isUsernameArleadyTalen(QString username);
private:
    QSqlDatabase db;
};

#endif // DATABASECONNECTION_H
