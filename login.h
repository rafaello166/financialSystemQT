#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QKeyEvent>
#include <mainwindow.h>
#include <QWidget>
#include <QtWidgets>
#include <QStackedWidget>

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

private:
    Ui::login *ui;
    void keyPressEvent(QKeyEvent * );
    QWidget *mainWindow;
    MainWindow* Profile;

};
#endif // LOGIN_H
