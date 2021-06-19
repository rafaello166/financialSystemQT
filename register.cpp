#include "register.h"
#include "ui_register.h"
#include "databaseconnection.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

// logika tworzenia konta
void Register::on_pushButton_register_clicked()
{
    // z pól do wypełnienia na stronie register zostają ściągnięte dane
    QString name = ui->lineEdit_name->text();
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_password->text();
    QString password_2 = ui->lineEdit_password_2->text();

    // connect to the database
    databaseConnection* db = new databaseConnection();

    if(db->isDataCorrect(name) && db->isDataCorrect(username) && db->isDataCorrect(password) && db->isDataCorrect(password_2))
        if(password == password_2) {
            db->createUser(name, username, password);

            QMessageBox::information(this, "Login", "User account has been created!");

            emit loginClicked();
        }
        else {
            QMessageBox::warning(this, "Login", "Passwords do not match!");
        }
    else
        QMessageBox::warning(this, "Login", "Each field should contain from 3 to 12 characters!");

}

// wysłanie sygnału do strony login
void Register::on_pushButton_login_clicked()
{
    emit loginClicked();
}

