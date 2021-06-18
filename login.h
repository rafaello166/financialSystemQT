#ifndef LOGIN_H
#define LOGIN_H

#include <mainwindow.h>
#include <register.h>

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
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

    void moveLogin();

private:
    Ui::login *ui;
    void keyPressEvent(QKeyEvent * );
    QWidget *mainWindow;
    MainWindow Profile;
    Register Register;

};
#endif // LOGIN_H
