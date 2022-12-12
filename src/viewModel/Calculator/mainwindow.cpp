#include "mainwindow.h"

#include <QPalette>
#include <QString>
#include <iostream>
#include <string>

#include "credit.h"
#include "plotter.h"
#include "ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      controller_(new Controller()),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Smart Calculator");
}

MainWindow::~MainWindow() {
  delete ui;
  delete controller_;
}

void MainWindow::update() {
  QString input = QString::fromStdString(controller_->getInputLine());
  QString output = QString::fromStdString(controller_->getOutputLine());

  ui->inputLine->setText(input);
  ui->outputLine->setText(output);
}

void MainWindow::on_btnX_clicked() {
  controller_->addToInputLine("x");
  update();
}

void MainWindow::on_btn0_clicked() {
  controller_->addToInputLine("0");
  update();
}

void MainWindow::on_btnDot_clicked() {
  controller_->addToInputLine(".");
  update();
}

void MainWindow::on_btn1_clicked() {
  controller_->addToInputLine("1");
  update();
}

void MainWindow::on_btn2_clicked() {
  controller_->addToInputLine("2");
  update();
}

void MainWindow::on_btn3_clicked() {
  controller_->addToInputLine("3");
  update();
}

void MainWindow::on_btn4_clicked() {
  controller_->addToInputLine("4");
  update();
}

void MainWindow::on_btn5_clicked() {
  controller_->addToInputLine("5");
  update();
}

void MainWindow::on_btn6_clicked() {
  controller_->addToInputLine("6");
  update();
}

void MainWindow::on_btn7_clicked() {
  controller_->addToInputLine("7");
  update();
}

void MainWindow::on_btn8_clicked() {
  controller_->addToInputLine("8");
  update();
}

void MainWindow::on_btn9_clicked() {
  controller_->addToInputLine("9");
  update();
}

void MainWindow::on_btnPlus_clicked() {
  controller_->addToInputLine("+");
  update();
}

void MainWindow::on_btnMinus_clicked() {
  controller_->addToInputLine("-");
  update();
}

void MainWindow::on_btnMul_clicked() {
  controller_->addToInputLine("*");
  update();
}

void MainWindow::on_btnDiv_clicked() {
  controller_->addToInputLine("/");
  update();
}

void MainWindow::on_btnEquals_clicked() {
  controller_->calculate();
  update();
}

void MainWindow::on_btnPlot_clicked() {
  Plotter plotter(this, controller_);
  plotter.setModal(true);
  plotter.exec();
}

void MainWindow::on_btnLBracket_clicked() {
  controller_->addToInputLine("(");
  update();
}

void MainWindow::on_btnRBracket_clicked() {
  controller_->addToInputLine(")");
  update();
}

void MainWindow::on_btnMod_clicked() {
  controller_->addToInputLine("mod");
  update();
}

void MainWindow::on_btnPow_clicked() {
  controller_->addToInputLine("^");
  update();
}

void MainWindow::on_btnExp_clicked() {
  controller_->addToInputLine("e");
  update();
}

void MainWindow::on_btnSqrt_clicked() {
  controller_->addToInputLine("sqrt");
  update();
}

void MainWindow::on_btnSin_clicked() {
  controller_->addToInputLine("sin");
  update();
}

void MainWindow::on_btnCos_clicked() {
  controller_->addToInputLine("cos");
  update();
}

void MainWindow::on_btnTan_clicked() {
  controller_->addToInputLine("tan");
  update();
}

void MainWindow::on_btnAsin_clicked() {
  controller_->addToInputLine("asin");
  update();
}

void MainWindow::on_btnAcos_clicked() {
  controller_->addToInputLine("acos");
  update();
}

void MainWindow::on_btnAtan_clicked() {
  controller_->addToInputLine("atan");
  update();
}

void MainWindow::on_btnLog_clicked() {
  controller_->addToInputLine("log");
  update();
}

void MainWindow::on_btnLn_clicked() {
  controller_->addToInputLine("ln");
  update();
}

void MainWindow::on_btnDel_clicked() {
  controller_->deleteElement();
  update();
}

void MainWindow::on_btnClear_clicked() {
  controller_->clearInputLine();
  update();
}

void MainWindow::on_varValue_editingFinished() {
  controller_->setVarValue(ui->varValue->text().toStdString());
}

void MainWindow::on_btnCreditCalc_clicked() {
  Credit credit(controller_);
  credit.setModal(true);
  credit.exec();
}
