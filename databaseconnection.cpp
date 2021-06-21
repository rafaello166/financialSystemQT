#include "databaseconnection.h"
//#include <QMainWindow>
#include <QMessageBox>
#include <iostream>

databaseConnection::databaseConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("financialsystem");
    db.setUserName("root");
    db.setPassword("");
    db.open();  //TODO: REALLY IMPORTANT

//    if(!db.open())
//        QMessageBox::warning(this, "Connection", "There are no connection to the database!");

}

//databaseConnection::~databaseConnection() {

//}

bool databaseConnection::createUser(QString first_name, QString username, QString password) {
    QSqlQuery *query = new QSqlQuery(db);

    if(!isUsernameArleadyTaken(username)) {
        query->prepare("INSERT INTO user (first_name, username, password) "
         "VALUES (?, ?, ?)");

        QString password_hash = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

        query->addBindValue(first_name);
        query->addBindValue(username);
        query->addBindValue(password_hash);
        query->exec();

        return true; //The account has been created successfully
    }

    delete query;

    return false;
}

bool databaseConnection::isUsernameArleadyTaken(QString username) {
    QSqlQuery *query = new QSqlQuery(db);

    if( query->exec("SELECT username FROM user WHERE username='"+username+"' ") ) {
        if( query->next() ) {
            if(query->value(0).toString() == username)
                return true;
        }
    }

    delete query;

    return false;
}

bool databaseConnection::isPasswordCorrect(QString username, QString password) {
    QSqlQuery *query = new QSqlQuery(db);

    QString password_hash = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

    if( query->exec("SELECT username FROM user WHERE username='"+username+"' AND password='"+password_hash+"' ") ) {
        if( query->next() ) {
            if(query->value(0).toString() == username) {
                return true;
            }
        }
    }

    delete query;

    return false;
}

bool databaseConnection::isDataCorrect(QString field) {
    field = field.simplified();
    field.replace( " ", "" );
    int length = field.toStdString().length();

    if(field != "")
        if(length >= 3 && length <= 12)
            return true;

    return false;
}

QVector<sqlTableModel> databaseConnection::getIncomeExpensesData(QString username) {
    QSqlQuery *query = new QSqlQuery(db);

    int i = 0;
    if( query->exec("SELECT Lp, income_expenses, category, amount FROM expenses WHERE username='"+username+"' ") ) {
        QVector<sqlTableModel> data;

        while( query->next() ) {

            sqlTableModel model;
            model.id = query->value(0).toInt();
            model.ie = query->value(1).toString();
            model.category = query->value(2).toString();
            model.amount = query->value(3).toDouble();
            data.push_back(model);

            i++;
        }

        return data;
    }

}

void databaseConnection::addIncomeExpenses(QString username, bool income_expenses, QString category, double amount) {
    QSqlQuery *query = new QSqlQuery(db);


    query->prepare("INSERT INTO expenses (username, income_expenses, category, amount) "
         "VALUES (?, ?, ?, ?)");

    query->addBindValue(username);
    query->addBindValue(income_expenses);
    query->addBindValue(category);
    query->addBindValue(amount);
    query->exec();

    delete query;
}

void databaseConnection::removeRow(QString username, int row) {
    QSqlQuery *query = new QSqlQuery(db);

    QString number = QString::number(row);
    query->prepare("DELETE FROM expenses WHERE username='"+username+"' and Lp='"+number+"' ");
    query->exec();

    delete query;
}
