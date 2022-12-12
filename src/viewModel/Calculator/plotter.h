#ifndef PLOTTER_H
#define PLOTTER_H

#include <QDialog>
#include <QVector>
#include <map>

#include "../../controller/controller.h"
#include "mainwindow.h"

namespace Ui {
class Plotter;
}
using namespace s21;
class Plotter : public QDialog {
  Q_OBJECT

 public:
  explicit Plotter(MainWindow *window, Controller *controller,
                   QWidget *parent = nullptr);
  ~Plotter();

 private slots:
  void on_scaleIn_clicked();

  void on_scaleOut_clicked();

 private:
  Ui::Plotter *ui;
  MainWindow *owner_;
  Controller *controller_;

  void drawPlot();
  void clearVectors();
  void increaseScale();
  void decreaseScale();
};

#endif  // PLOTTER_H
