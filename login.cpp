#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <register.h>



financialSystem::financialSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::financialSystem)
{
    ui->setupUi(this);
}

financialSystem::~financialSystem()
{
    delete ui;
}

void financialSystem::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_password->text();

    if(username == "test" && password == "pass") {
        QMessageBox::information(this, "Login", "Logged in successfully!");
        hide();
        mainWindow = new QMainWindow(this);
        mainWindow->show();
    }
    else {
        QMessageBox::warning(this, "Login", "Username or password is not correct.");
//        ui->lineEdit_user->setText(""); //TODO: cursor doesn't move on 'login field'
        ui->lineEdit_password->setText("");

    }


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("financialsystem");
    db.setUserName("root");
    db.setPassword("");


    if(db.open()) {
        QMessageBox::information(this, "Connection", "ok");


    }
    else {
        QMessageBox::warning(this, "Connection", "not ok");
    }


}

void financialSystem::keyPressEvent(QKeyEvent *event) {
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        on_pushButton_login_clicked();
    }
}

void financialSystem::on_pushButton_register_clicked()
{
    Register *registerPage = new Register;
    registerPage->show();
    hide();
}
