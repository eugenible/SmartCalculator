#include "credit.h"

#include <QMap>
#include <QString>
#include <iostream>

#include "../../calcModel/credit_data.h"
#include "ui_credit.h"

Credit::Credit(Controller *controller, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Credit),
      controller_(controller),
      map_(),
      monthMap_(),
      percentageMap_() {
  ui->setupUi(this);
  ui->btnAnnuity->click();
  setWindowTitle("Credit Calculator");
  for (int i = 0; i < 25; ++i) {
    if (i < 10) {
      QString value = QString::number(i * 100000);
      map_[i] = value.insert(3, " ");
    }
    if (i >= 10 && i < 20) {
      QString value = QString::number((i - 9) * 1000000);
      map_[i] =
          value.insert(value.length() - 3, " ").insert(value.length() - 7, " ");
    }

    if (i >= 20 && i <= 23) {
      QString value = QString::number(10 * (i - 18)) + " 000 000";
      map_[i] = value;
    }
    if (i == 24) map_[i] = "100 000 000";
  }

  monthMap_[0] = "1";
  monthMap_[1] = "3";
  monthMap_[2] = "6";
  monthMap_[3] = "12";
  monthMap_[4] = "24";
  monthMap_[5] = "36";
  monthMap_[6] = "48";
  monthMap_[7] = "60";
  monthMap_[8] = "120";
  monthMap_[9] = "180";
  monthMap_[10] = "240";

  on_btnAnnuity_clicked();
  on_timeCombobox_currentIndexChanged(0);
  on_percentageCombobox_currentIndexChanged(0);
  on_creditAmountSlider_valueChanged(0);
}

Credit::~Credit() { delete ui; }

void Credit::on_calculate_clicked() {
  CreditData data = controller_->getCreditData();
  ui->monthlyPay->setText(QString::fromStdString(data.getAveragePayment()));
  ui->overallPay->setText(QString::fromStdString(data.getOverallPayment()));
  ui->overpayment->setText(QString::fromStdString(data.getOverpayment()));
}

void Credit::on_btnAnnuity_clicked() { controller_->setStrType("Annuity"); }

void Credit::on_btnDiff_clicked() { controller_->setStrType("Differentiated"); }

void Credit::on_timeCombobox_currentIndexChanged(int index) {
  controller_->setStrTime(monthMap_[index].replace(" ", "").toStdString());
}

void Credit::on_percentageCombobox_currentIndexChanged(int index) {
  controller_->setStrPercentage(
      ui->percentageCombobox->currentText().toStdString());
}

void Credit::on_creditAmountSlider_valueChanged(int value) {
  ui->creditAmountLabel->setText(map_.value(value));
  controller_->setStrCreditAmount(map_[value].replace(" ", "").toStdString());
}
