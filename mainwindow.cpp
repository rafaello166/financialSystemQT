#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

int sqlAmount = 0;
QString sqlAmountString = QString::number(sqlAmount);
QString sqlWelcomeString = "custom welcome text from sql";

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
    amountExpenses = ui->spinBox;
    amountIncome->setRange(0, 10000);
    amountExpenses->setRange(0, 10000);

    categoryIncome = ui->lineEdit_2;
    categoryExpenses = ui->lineEdit_3;

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
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
    QString category = categoryExpenses->text();
    QString amount = amountExpenses->cleanText();
    int money = amountExpenses->value();
    sqlAmount -= money;
    QString amountString = QString::number(sqlAmount);
    balanceLabel->setText({amountString});
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Expenses"));
    tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
    tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
}


void MainWindow::on_pushButton_3_clicked()
{
    login *loginPage = new login;
    hide();
    loginPage->show();
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
    if (count > 0) {
        sqlAmount=0;
        QString amountString = QString::number(sqlAmount);
        balanceLabel->setText({amountString});
        ui->tableWidget->setRowCount(0);
    }
    else {
        QMessageBox::critical(this, "Error", "There are no entries left");
    }
}

