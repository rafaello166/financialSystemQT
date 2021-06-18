#include "piechart.h"
#include "ui_piechart.h"

PieChart::PieChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    series->append("Hm 25%", 1);
    series->append("Hm 25%", 1);
    series->append("Hm 25%", 1);
    series->append("Hm 25%", 1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Expenses Donut Chart");
    chart->setTheme(QChart::ChartThemeDark);

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);
}

PieChart::~PieChart()
{
    delete ui;
}
