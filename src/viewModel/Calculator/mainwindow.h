#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
using namespace s21;
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Controller *controller_;

  void update();

 private slots:

  void on_btnX_clicked();

  void on_btn0_clicked();

  void on_btnDot_clicked();

  void on_btn1_clicked();

  void on_btn2_clicked();

  void on_btn3_clicked();

  void on_btn4_clicked();

  void on_btn5_clicked();

  void on_btn6_clicked();

  void on_btn7_clicked();

  void on_btn8_clicked();

  void on_btn9_clicked();

  void on_btnPlus_clicked();

  void on_btnMinus_clicked();

  void on_btnMul_clicked();

  void on_btnDiv_clicked();

  void on_btnEquals_clicked();

  void on_btnPlot_clicked();

  void on_btnLBracket_clicked();

  void on_btnRBracket_clicked();

  void on_btnMod_clicked();

  void on_btnPow_clicked();

  void on_btnExp_clicked();

  void on_btnSqrt_clicked();

  void on_btnSin_clicked();

  void on_btnCos_clicked();

  void on_btnTan_clicked();

  void on_btnAsin_clicked();

  void on_btnAcos_clicked();

  void on_btnAtan_clicked();

  void on_btnLog_clicked();

  void on_btnLn_clicked();

  void on_btnDel_clicked();

  void on_btnClear_clicked();

  void on_varValue_editingFinished();

  void on_btnCreditCalc_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
