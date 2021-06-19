#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

// databaseconnection to klasa służąca do połączenia się z bazą danych MySQL

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

extern QString firstname;

// Zainicjowanie klasy potrzebnej nam później do wektora - będzie służyła jako dodawanie osobnych wpisów
// Znajdują się w niej 3 zmienne
// ie - Income/Expenses
// category - Kategoria
// amount - Ilość

class sqlTableModel {
public:
    QString ie;
    QString category;
    double amount;
};

// W poniższej klasie znajdują się wszystkie potrzebne funkcje z których będziemy korzystać do połączenia się z bazą danych
// getIncomeExpensesData - daje nam tabelowe dane użytkownika
// createUser - tworzy użytkownika
// isUsernameAlreadyTaken - sprawdza czy taki użytkownik już istnieje
// isPasswordCorrect - sprawdza czy hasło jest poprawne
// isDataCorrect - sprawdza czy dane się zgadzają

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

// Zainicjowanie zmiennej db która będzie służyła nam jako odwołanie do naszej bazy danych
private:
    QSqlDatabase db;
    int test = 0;
};

#endif // DATABASECONNECTION_H
