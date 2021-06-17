#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
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
    QMainWindow *mainWindow;

};
#endif // LOGIN_H
