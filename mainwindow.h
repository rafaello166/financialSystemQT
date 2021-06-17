#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtWidgets>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
//#include <string>
//#include <cstring>
//#include <QDoubleValidator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTableWidget* tableWidget;
    QLabel* welcomeLabel;
    QLabel* balanceLabel;
    QSpinBox* amountIncome;
    QSpinBox* amountExpenses;
    QLineEdit* categoryExpenses;
    QLineEdit* categoryIncome;
};

#endif // MAINWINDOW_H
