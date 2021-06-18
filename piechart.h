#ifndef PIECHART_H
#define PIECHART_H

#include <QDialog>

namespace Ui {
class PieChart;
}

class PieChart : public QDialog
{
    Q_OBJECT

public:
    explicit PieChart(QWidget *parent = nullptr);
    ~PieChart();

private:
    Ui::PieChart *ui;
};

#endif // PIECHART_H
