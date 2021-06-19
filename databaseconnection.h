#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

class sqlTableModel {
public:
    QString ie;
    QString category;
    double amount;
};

class databaseConnection
{
public:
    databaseConnection();
    QVector<sqlTableModel> getIncomeExpensesData(QString username);
    bool createUser(QString first_name, QString username, QString password);
    bool isUsernameArleadyTaken(QString username);
    bool isPasswordCorrect(QString username, QString password);
    bool isDataCorrect(QString field);
    void setTest();
    int getTest();

private:
    QSqlDatabase db;
    int test = 0;
};

#endif // DATABASECONNECTION_H
