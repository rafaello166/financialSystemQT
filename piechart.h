#ifndef PIECHART_H
#define PIECHART_H

// piechart to klasa która wyświetla nam wykres w kształcie 'ciasta'

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

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
