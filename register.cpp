#include "register.h"
#include "ui_register.h"
#include "login.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_login_clicked()
{
    login *loginPage = new login;
    loginPage->show();
    hide();
}

