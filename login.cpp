#include "login.h"
#include "ui_login.h"
#include "databaseconnection.h"
#include <QMessageBox>

// connect to the database
databaseConnection* db = new databaseConnection();

QString firstname = "test";

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    // Stworzenie UI loginu
    ui->setupUi(this);

    // Umożliwienie płynnej zmiany z strony login na stronę register i profile
    ui->centralstackedWidget->insertWidget(1, &Register);
    ui->centralstackedWidget->insertWidget(2, &Profile);
    connect(&Register, SIGNAL(loginClicked()), this, SLOT(moveLogin()));
    connect(&Profile, SIGNAL(logoutClicked()), this, SLOT(moveLogin()));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{

    // z pól do wypełnienia na stronie login zostają ściągnięte dane
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_password->text();


//    // logowanie na testowe konto
//    if (username == "test" && password == "pass") {
//        ui->centralstackedWidget->setCurrentIndex(2);
////        MainWindow *profilePage = new MainWindow;
////        hide();
////        profilePage->show();
//    }


    if(db->isDataCorrect(username) && db->isDataCorrect(password))
        if(db->isPasswordCorrect(username, password)) {
            QMessageBox::information(this, "Login", "Logged in successfully!");

            ui->centralstackedWidget->setCurrentIndex(2);

//            MainWindow *profilePage = new MainWindow;
//            hide();
//            profilePage->show();
        }
        else {
            QMessageBox::warning(this, "Login", "Username or password is incorrect.");

            ui->lineEdit_password->setText("");
        }
    else
        QMessageBox::warning(this, "Login", "Username or password is incorrect.");

}

// umożliwienie zalogowania za pomocą entera
void login::keyPressEvent(QKeyEvent *event) {
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        on_pushButton_login_clicked();
    }
}

// logika przycisku do przejścia na stronę register
void login::on_pushButton_register_clicked()
{
    ui->centralstackedWidget->setCurrentIndex(1);
}

// Odpowiedź na sygnał z strony register - powrót na stronę login
void login::moveLogin()
{
    ui->centralstackedWidget->setCurrentIndex(0);
}
