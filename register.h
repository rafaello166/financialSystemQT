#ifndef REGISTER_H
#define REGISTER_H

#include <mainwindow.h>

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
#include <QStackedWidget>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QWidget
{
    Q_OBJECT

public:
    Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_login_clicked();

signals:
    void loginClicked();

private:
    Ui::Register *ui;
//    void keyPressEvent(QKeyEvent * );
    MainWindow Profile;
};

#endif // REGISTER_H
