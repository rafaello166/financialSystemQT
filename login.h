#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class financialSystem; }
QT_END_NAMESPACE

class financialSystem : public QMainWindow
{
    Q_OBJECT

public:
    financialSystem(QWidget *parent = nullptr);
    ~financialSystem();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::financialSystem *ui;
    void keyPressEvent(QKeyEvent * );
    QMainWindow *mainWindow;

};
#endif // LOGIN_H
