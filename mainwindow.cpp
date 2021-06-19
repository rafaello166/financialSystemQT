#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "piechart.h"
#include "databaseconnection.h"

int sqlAmount = 0;
QString sqlAmountString = QString::number(sqlAmount);
QString sqlWelcomeString = "QString::number(db->getTest())";

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableWidget = ui->tableWidget;
    tableWidget->setColumnWidth(0,100);
    tableWidget->setColumnWidth(1,125);
    tableWidget->setColumnWidth(2,125);

    welcomeLabel = ui->label_2;
    welcomeLabel->setText({sqlWelcomeString});

    balanceLabel = ui->label;
    balanceLabel->setText({sqlAmountString});

    amountIncome = ui->spinBox_2;
    amountIncome->setRange(1, 10000);
    categoryIncome = ui->lineEdit_2;

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(0, this->width()/8);
    ui->tableWidget->setColumnWidth(1, this->width()/3);
    ui->tableWidget->setColumnWidth(2, this->width()/8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString category = categoryIncome->text();
    QString amount = amountIncome->cleanText();
    int money = amountIncome->value();
    sqlAmount += money;
    QString amountString = QString::number(sqlAmount);
    balanceLabel->setText({amountString});
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Income"));
    tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
    tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
}


void MainWindow::on_pushButton_2_clicked()
{
    QString category = categoryIncome->text();
    QString amount = amountIncome->cleanText();
    int money = amountIncome->value();
    sqlAmount -= money;
    QString amountString = QString::number(sqlAmount);
    balanceLabel->setText({amountString});
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Expenses"));
    tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
    tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
    tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);
}


void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        login *loginPage = new login;
        hide();
        loginPage->show();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    int count = ui->tableWidget->rowCount();
    if (count > 0) {
        int row = ui->tableWidget->currentRow();
        QString category = ui->tableWidget->item(row, 0)->text();
        QString amountS = ui->tableWidget->item(row, 2)->text();
        int amount = amountS.split(" ")[0].toInt();
        if (category == "Income") {
            sqlAmount -= amount;
        }
        else if (category == "Expenses") {
            sqlAmount += amount;
        }
        QString amountString = QString::number(sqlAmount);
        balanceLabel->setText({amountString});
        ui->tableWidget->removeRow(row);
    }
    else {
        QMessageBox::critical(this, "Error", "There are no entries left");
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    int count = ui->tableWidget->rowCount();
    if (count < 1) {
        QMessageBox::critical(this, "Error", "There are no entries left");
    }
    if (count > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "WARNING", "Are you sure you want to clear all entries?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            sqlAmount=0;
            QString amountString = QString::number(sqlAmount);
            balanceLabel->setText({amountString});
            ui->tableWidget->setRowCount(0);
        }
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    PieChart piechart;
    piechart.setModal(true);
    piechart.exec();
}

