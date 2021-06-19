#include "login.h"
#include "ui_login.h"
#include "databaseconnection.h"
#include <QMessageBox>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->centralstackedWidget->insertWidget(1, &Register);
//    ui->centralstackedWidget->insertWidget(2, &Profile);
    connect(&Register, SIGNAL(loginClicked()), this, SLOT(moveLogin()));
//    connect(&Profile, SIGNAL(logoutClicked()), this, SLOT(jumpLogin()));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_password->text();

    // connect to the database
    databaseConnection* db = new databaseConnection();

    if(db->isDataCorrect(username) && db->isDataCorrect(password))
        if(db->isPasswordCorrect(username, password)) {
            QMessageBox::information(this, "Login", "Logged in successfully!");

            MainWindow *profilePage = new MainWindow;

            hide();
            profilePage->show();;
        }
        else {
            QMessageBox::warning(this, "Login", "Username or password is incorrect.");

            ui->lineEdit_password->setText("");
        }
    else
        QMessageBox::warning(this, "Login", "Username or password is incorrect.");

}

void login::keyPressEvent(QKeyEvent *event) {
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        on_pushButton_login_clicked();
    }
}

void login::on_pushButton_register_clicked()
{
    ui->centralstackedWidget->setCurrentIndex(1);
}

void login::moveLogin()
{
    ui->centralstackedWidget->setCurrentIndex(0);
}
