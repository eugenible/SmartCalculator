#include "plotter.h"

#include <QVector>
#include <iostream>

#include "../../calcModel/plot_data.h"
#include "../../controller/controller.h"
#include "ui_plotter.h"

using s21::PlotData;

Plotter::Plotter(MainWindow *window, Controller *controller, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Plotter),
      owner_(window),
      controller_(controller) {
  ui->setupUi(this);
  drawPlot();
}

void Plotter::increaseScale() {
  if (controller_->increaseScale()) drawPlot();
}

void Plotter::decreaseScale() {
  if (controller_->decreaseScale()) drawPlot();
}

Plotter::~Plotter() { delete ui; }

void Plotter::on_scaleIn_clicked() { decreaseScale(); }

void Plotter::on_scaleOut_clicked() { increaseScale(); }

void Plotter::drawPlot() {
  PlotData result = controller_->getPlotCoordinates();
  if (!result.isValidExpression()) return;
  std::vector<double> x = result.getXCoords();
  std::vector<double> y = result.getYCoords();
  QVector<double> xCoords = QVector<double>(x.begin(), x.end());
  QVector<double> yCoords = QVector<double>(y.begin(), y.end());
  ui->plot->xAxis->setRange(result.getMin(), result.getMax());
  ui->plot->yAxis->setRange(result.getMin(), result.getMax());
  ui->plot->addGraph();
  ui->plot->graph(0)->addData(xCoords, yCoords);
  ui->plot->replot();
  ui->plot->setInteraction(QCP::iRangeZoom, true);
  ui->plot->setInteraction(QCP::iRangeDrag, true);
}
