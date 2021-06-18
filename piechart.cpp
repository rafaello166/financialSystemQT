#include "piechart.h"
#include "ui_piechart.h"

PieChart::PieChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
}

PieChart::~PieChart()
{
    delete ui;
}
