#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "databaseconnection.h"

#include "piechart.h"
#include "ui_piechart.h"

double sqlAmount = 0;
double sqlExpenses = 0;

class sqlTableModel {
public:
    QString ie;
    QString category;
    double amount;
};

sqlTableModel model;
QVector<sqlTableModel> sqlTable;

QString sqlAmountString = QString::number(sqlAmount);
QString sqlBalanceString = QString("Your balance is: %1").arg(sqlAmountString);
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
    welcomeLabel->setText(sqlWelcomeString);

    balanceLabel = ui->label;
    balanceLabel->setText(sqlBalanceString);

    amountIncome = ui->doubleSpinBox_2;
    amountIncome->setRange(0, 10000);
    amountIncome->setSuffix(" zł");
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
    double money = amountIncome->value();
    if (category != "" && money != 0) {
        QString amount = amountIncome->cleanText() + " zł";
        sqlAmount += money;
        QString amountString = QString::number(sqlAmount);
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Income"));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
        tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
        tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);

        model.ie = "Income";
        model.category = category;
        model.amount = money;
        sqlTable.push_back(model);
    }
    else if (category == "") {
        QMessageBox::critical(this, "Error", "Category can't be blank");
    }
    else if (money == 0) {
        QMessageBox::critical(this, "Error", "Amount can't be equal to 0");
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    QString category = categoryIncome->text();
    double money = amountIncome->value();
    if (category != "" && money != 0) {
        QString amount = amountIncome->cleanText() + " zł";

        sqlAmount -= money;
        sqlExpenses += money;
        QString amountString = QString::number(sqlAmount);
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Expenses"));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
        tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
        tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);

        model.ie = "Expenses";
        model.category = category;
        model.amount = money;
        sqlTable.push_back(model);
    }
    else if (category == "") {
        QMessageBox::critical(this, "Error", "Category can't be blank");
    }
    else if (money == 0) {
        QMessageBox::critical(this, "Error", "Amount can't be equal to 0");
    }
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
        int index = amountS.indexOf(',');
        double amount = amountS.split(" ")[0].replace(index, 1, '.').toDouble();
        if (count > 1) {
            if (category == "Income") {
                sqlAmount -= amount;
            }
            else if (category == "Expenses") {
                sqlAmount += amount;
                sqlExpenses -= amount;
            }
        }
        if (count == 1) {
            sqlAmount = 0;
            sqlExpenses = 0;
        }
        QString amountString = QString::number(sqlAmount);
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);
        ui->tableWidget->removeRow(row);
        sqlTable.removeAt(row);
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
            sqlExpenses=0;
            QString amountString = QString::number(sqlAmount);
            QString balanceString = QString("Your balance is: %1").arg(amountString);
            balanceLabel->setText(balanceString);
            ui->tableWidget->setRowCount(0);
            sqlTable.clear();
        }
    }
}

PieChart::PieChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    for (int i = 0; i < sqlTable.size(); i++) {
        if (sqlTable[i].ie == "Expenses") {
            if (series->count() == 0) {
                series->append(sqlTable[i].category, sqlTable[i].amount)->setLabelVisible();
                qInfo() << "Slice value: " << series->slices().at(0)->value();
            }
            else {
                int j = 0;
                while (true) {
                    if (series->slices().at(j)->label() == sqlTable[i].category) {
                        double newVal = series->slices().at(j)->value() + sqlTable[i].amount;
                        series->slices().at(j)->setValue(newVal);
                        qInfo() << "Slice value: " << series->slices().at(j)->value();
                        break;
                    }
                    if (j == series->count() - 1) {
                        series->append(sqlTable[i].category, sqlTable[i].amount)->setLabelVisible();
                        qInfo() << "Slice value: " << series->slices().at(j)->value();
                        break;
                    }
                    j++;
                }
            }
        }
        qInfo() << "Sum value: " << series->sum();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Expenses Donut Chart");
    chart->setTheme(QChart::ChartThemeDark);

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);
}

PieChart::~PieChart()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()
{
    PieChart piechart;
    piechart.setModal(true);
    piechart.exec();
}

