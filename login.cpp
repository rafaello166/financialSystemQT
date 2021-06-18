#include "login.h"
#include "ui_login.h"
#include "databaseconnection.h"

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

    if(username == "test" && password == "pass") {
        QMessageBox::information(this, "Login", "Logged in successfully!");
//        ui->centralstackedWidget->setCurrentIndex(2);
                MainWindow *profilePage = new MainWindow;
                hide();
                profilePage->show();;
    }
    else {
        QMessageBox::warning(this, "Login", "Username or password is not correct.");
//        ui->lineEdit_user->setText(""); //TODO: cursor doesn't move on 'login field'
        ui->lineEdit_password->setText("");

    }


//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("localhost");
//    db.setDatabaseName("login");
//    db.setUserName("root");
//    db.setPassword("");


//    if(db.open()) {
//        QMessageBox::information(this, "Connection", "ok");


//    }
//    else {
//        QMessageBox::warning(this, "Connection", "not ok");
//    }


    databaseConnection* bt = new databaseConnection();
    bt->createUser("ola", "mm", "olamm", "123");
//    bt->isUsernameArleadyTalen("macwiec");


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
    qInfo() << "WORKING";
    ui->centralstackedWidget->setCurrentIndex(0);
}
