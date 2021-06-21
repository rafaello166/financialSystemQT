#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// mainwindow to klasa która wyświetla nam stronę profilu

#include <QMainWindow>
#include <QWidget>
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
#include <QDoubleSpinBox>
#include <QStackedWidget>
#include <QPixmap>
#include <QMap>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Poniżej znajdują się funkcje przypisane odpowiedniemu przyciskowi/sloty

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    // Musimy zainicjować odpowiednie widgety które chcemy później zmieniać za pomocą kodu

signals:
    void logoutClicked();

private:
    Ui::MainWindow *ui;
    QWidget *mainWindow;
    QTableWidget* tableWidget;
    QLabel* welcomeLabel;
    QLabel* balanceLabel;
    QDoubleSpinBox* amountIncome;
    QDoubleSpinBox* amountExpenses;
    QLineEdit* categoryExpenses;
    QLineEdit* categoryIncome;
};

#endif // MAINWINDOW_H
