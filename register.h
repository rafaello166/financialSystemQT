#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_register_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
