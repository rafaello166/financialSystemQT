#include <QtSql>
#include <QSqlDatabase>

bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("financialsystem");
    db.setUserName("root");
    db.setPassword("");

    if(db.open())
        return true;
    else
        return false;
}

//bool registerBinder() {
//    QSqlQuery query(db);
//    query.prepare("INSERT INTO cd (id, artistid, title, year) "
//     "VALUES (?, ?, ?, ?)");
//    query.addBindValue(203);
//    query.addBindValue(102);
//    query.addBindValue(QString("Living in America"));
//    query.addBindValue(2002);
//    query.exec();
//}
