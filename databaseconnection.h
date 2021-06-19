#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

class databaseConnection
{
public:
    databaseConnection();
    bool createUser(QString first_name, QString username, QString password);
    bool isUsernameArleadyTaken(QString username);
    bool isPasswordCorrect(QString username, QString password);
    bool isDataCorrect(QString field);

private:
    QSqlDatabase db;
};

#endif // DATABASECONNECTION_H
