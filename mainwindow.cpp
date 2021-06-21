#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "databaseconnection.h"

#include "piechart.h"
#include "ui_piechart.h"

// Zmienne pomocniczne repezentujące odpowiednio saldo oraz ilość wydatków

double sqlAmount = 0;
double sqlExpenses = 0;

//databaseConnection* db = new databaseConnection();
extern databaseConnection* db;

// Stworzenie modelu klasy dzięki której będzie mogli dodawać wpisy do naszego wektora zainicjowanego poniżej
sqlTableModel model;
QVector<sqlTableModel> sqlTable; // = db->getIncomeExpensesData(username);


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ustawienie wiadomości powitalnej w UI

    // Wiadomość powitalna na stronie profilu
    QString sqlWelcomeString = QString("Hi %1! Welcome to your profile.").arg(firstname);
    welcomeLabel = ui->label_2;
    welcomeLabel->setText(sqlWelcomeString);

    // Dodatkowa konfiguracja pól do wpisywania ilości i kategorii
    amountIncome = ui->doubleSpinBox_2;
    amountIncome->setRange(0, 10000);
    amountIncome->setSuffix(" zł");
    categoryIncome = ui->lineEdit_2;

    // Dodatkowa konfiguracja tabeli wydatków i dochodów
    tableWidget = ui->tableWidget;
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setColumnWidth(0, this->width()/8);
    tableWidget->setColumnWidth(1, this->width()/3);
    tableWidget->setColumnWidth(2, this->width()/8);

//    // testowe dane
//    for(int z = 0; z < 10; z++) {
//        model.ie = "Expenses";
//        model.category = "STATIC";
//        model.amount = 100.01;
//        sqlTable.push_back(model);
//    }

    // pobieranie danych z bazy danych
    QVector<sqlTableModel> sqldata = db->getIncomeExpensesData(firstname);

    // wczytanie danych z bazy danych
    for (int g = 0; g < sqldata.size(); g++) {
        QString amount = QString::number(sqldata[g].amount) + " zł";
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem(QVariant(sqldata[g].ie).toBool() ? "Income" : "Expenses"));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem(sqldata[g].category));
        tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem(amount));
        tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);
        if (!QVariant(sqldata[g].ie).toBool()) { // Income
            sqlAmount += sqldata[g].amount;
        }
        else if (QVariant(sqldata[g].ie).toBool()) { // Expenses
            sqlAmount -= sqldata[g].amount;
            sqlExpenses += sqldata[g].amount;
        }
    }

    // ustawienie wiadomości ukazującej saldo
    balanceLabel = ui->label;
    QString amountString = QString::number(sqlAmount) + " zł";
    QString balanceString = QString("Your balance is: %1").arg(amountString);
    balanceLabel->setText(balanceString);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Logika klikania przycisku do dodawania dochodów
void MainWindow::on_pushButton_clicked()
{
    QString category = categoryIncome->text();
    double money = amountIncome->value();
    if (category != "" && money != 0) {
        QString amount = amountIncome->cleanText() + " zł";
        sqlAmount += money;
        QString amountString = QString::number(sqlAmount) + " zł";
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Income"));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
        tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
        tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);

        // Wykorzystanie na początku stworzonego modelu do dowania wpisów do wektora (sqlTable)
//        model.ie = "Income";
//        model.category = category;
//        model.amount = money;
//        sqlTable.push_back(model);

        db->addIncomeExpenses(firstname, 0, category, money);
    }
    // Pole kategorii nie może być puste
    else if (category == "") {
        QMessageBox::critical(this, "Error", "Category can't be blank");
    }
    // Pole wpisywanej ilości nie może być puste
    else if (money == 0) {
        QMessageBox::critical(this, "Error", "Amount can't be equal to 0");
    }
}

// Logika klikania przycisku do dodawania wydatków
void MainWindow::on_pushButton_2_clicked()
{
    QString category = categoryIncome->text();
    double money = amountIncome->value();
    if (category != "" && money != 0) {
        QString amount = amountIncome->cleanText() + " zł";

        sqlAmount -= money;
        sqlExpenses += money;
        QString amountString = QString::number(sqlAmount) + " zł";
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, new QTableWidgetItem("Expenses"));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, new QTableWidgetItem({category}));
        tableWidget->setItem(tableWidget->rowCount()-1, 2, new QTableWidgetItem({amount}));
        tableWidget->setCurrentCell(tableWidget->rowCount()-1, 0);

//        model.ie = "Expenses";
//        model.category = category;
//        model.amount = money;
//        sqlTable.push_back(model);

        db->addIncomeExpenses(firstname, 1, category, money);
    }
    else if (category == "") {
        QMessageBox::critical(this, "Error", "Category can't be blank");
    }
    else if (money == 0) {
        QMessageBox::critical(this, "Error", "Amount can't be equal to 0");
    }
}

// Logika klikania przycisku do wylogowywania się
void MainWindow::on_pushButton_3_clicked()
{
    // Wyskakujące okienko które pyta się nas czy na pewno chcemy się wylogować
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit logoutClicked();
//        login *loginPage = new login;
//        hide();
//        loginPage->show();
    }
}

// Logika klikania przycisku do odejmowania wpisów z tabeli
void MainWindow::on_pushButton_4_clicked()
{
    int count = tableWidget->rowCount();
    if (count > 0) {
        int row = tableWidget->currentRow();
        QString category = tableWidget->item(row, 0)->text();
        QString amountS = tableWidget->item(row, 2)->text();
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
        QString amountString = QString::number(sqlAmount) + " zł";
        QString balanceString = QString("Your balance is: %1").arg(amountString);
        balanceLabel->setText(balanceString);


        // pobieranie danych z bazy danych
        QVector<sqlTableModel> sqldata = db->getIncomeExpensesData(firstname);

        // usuwanie z bazy danych
        int removeAtSql = sqldata[row].id;
        db->removeRow(firstname, removeAtSql);

        // usuwanie z ekranu widoku
        tableWidget->removeRow(row);
        sqldata.removeAt(row);

    }
    // Jeżeli nie ma żadnych wpisów w tabeli to nie możemy nic odjąć
    else {
        QMessageBox::critical(this, "Error", "There are no entries left");
    }
}

// Logika klikania przycisku do czyszczenia danych
void MainWindow::on_pushButton_5_clicked()
{
    int count = tableWidget->rowCount();
    if (count < 1) {
        QMessageBox::critical(this, "Error", "There are no entries left");
    }
    // Wyskakujące okienko które pyta się nas czy na pewno chcemy wyczyścić wszystkie wpisy
    if (count > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "WARNING", "Are you sure you want to clear all entries?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            sqlAmount=0;
            sqlExpenses=0;
            QString amountString = QString::number(sqlAmount) + " zł";
            QString balanceString = QString("Your balance is: %1").arg(amountString);
            balanceLabel->setText(balanceString);
            tableWidget->setRowCount(0);
            sqlTable.clear();


            // pobieranie danych z bazy danych
            QVector<sqlTableModel> sqldata = db->getIncomeExpensesData(firstname);

            // usuwanie z bazy danych wszystkich kolumn
            for (int g = 0; g < sqldata.size(); g++)
                db->removeRow(firstname, sqldata[g].id);

        }
    }
}

// Logika kryjąca się za stworzonym wykresem
PieChart::PieChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();

    // pobieranie danych z bazy danych
    QVector<sqlTableModel> sqldata = db->getIncomeExpensesData(firstname);

    // Ustawiamy nasz wykres by wyglądał jak donut
    series->setHoleSize(0.35);

    // Dodajemy do naszego wykresu dane z tabeli
    for (int i = 0; i < sqldata.size(); i++) {
        if (QVariant(sqldata[i].ie).toBool()) { // Expenses
            // Jeżeli nie ma żadnego wpisu zapisanego na naszym wykresie to po prostu dodaje ten wpis
            if (series->count() == 0) {
                series->append(sqldata[i].category, sqldata[i].amount)->setLabelVisible();
            }
            // Natomiast jeśli już jakieś są to sprawdza wszystkie czy nie istnieje już wpis o takiej samej kategorii
            // Jeśli istnieje to do zapisanego już wpisu dodaje wartość tego drugie wpisu przez co ten pierwszy się powiększa
            // Jeśli nie istnieje to po prostu dodaje nowy wpis
            else {
                int j = 0;
                while (true) {
                    if (series->slices().at(j)->label() == sqldata[i].category) {
                        double newVal = series->slices().at(j)->value() + sqldata[i].amount;
                        series->slices().at(j)->setValue(newVal);
                        break;
                    }
                    if (j == series->count() - 1) {
                        series->append(sqldata[i].category, sqldata[i].amount)->setLabelVisible();
                        break;
                    }
                    j++;
                }
            }
        }
    }

    // Dodatkowe ustawienia wykresu takie jak animacja czy motyw
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

// Logika klikania przycisku do pokazania pie chartu
void MainWindow::on_pushButton_6_clicked()
{
    PieChart piechart;
    piechart.setModal(true);
    piechart.exec();
}

