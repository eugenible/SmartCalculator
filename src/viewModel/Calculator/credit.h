#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QMap>

#include "../../controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(Controller *controller, QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_calculate_clicked();

  void on_btnAnnuity_clicked();

  void on_btnDiff_clicked();

  void on_timeCombobox_currentIndexChanged(int index);

  void on_percentageCombobox_currentIndexChanged(int index);

  void on_creditAmountSlider_valueChanged(int value);

 private:
  Ui::Credit *ui;
  Controller *controller_;
  QMap<int, QString> map_;
  QMap<int, QString> monthMap_;
  QMap<int, QString> percentageMap_;

  void calculate();
};

#endif  // CREDIT_H
