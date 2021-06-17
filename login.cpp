    #include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "register.h"



login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
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
    db.setDatabaseName("login");
    db.setUserName("root");
    db.setPassword("");


    if(db.open()) {
        QMessageBox::information(this, "Connection", "ok");


    }
    else {
        QMessageBox::warning(this, "Connection", "not ok");
    }

}

void login::keyPressEvent(QKeyEvent *event) {
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        on_pushButton_login_clicked();
    }
}

void login::on_pushButton_register_clicked()
{
    Register *registerPage = new Register;
    registerPage->show();
    hide();
}
