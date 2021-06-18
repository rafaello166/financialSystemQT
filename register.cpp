#include "register.h"
#include "ui_register.h"

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

void Register::on_pushButton_register_clicked()
{
    MainWindow *profilePage = new MainWindow;
    profilePage->show();
    hide();
}

void Register::on_pushButton_login_clicked()
{
    emit loginClicked();
}

