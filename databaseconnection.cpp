#include "databaseconnection.h"
//#include <QMainWindow>
//#include <QMessageBox>
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
    // db disconnect
//}

bool databaseConnection::createUser(QString first_name, QString last_name, QString username, QString password) {
    QSqlQuery *query = new QSqlQuery(db);
        query->prepare("INSERT INTO user (first_name, last_name, username, password) "
         "VALUES (?, ?, ?, ?)");
        query->addBindValue(first_name);
        query->addBindValue(last_name);
        query->addBindValue(username);
        query->addBindValue(password);
        query->exec();
}

std::string databaseConnection::isUsernameArleadyTalen(QString username) {
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("SELECT username FROM user WHERE username='"+username+"' ");

//    if(query->exec( )){
//        std::string test = query->value(0).toString();

//        std::cout << test;
//    }

}
