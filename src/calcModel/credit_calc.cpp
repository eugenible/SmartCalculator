#include "credit_calc.h"

#include <cstdio>
#include <iostream>
#include <string>

#include "calculator.h"
#include "credit_data.h"

using namespace s21;

CreditCalculator::CreditCalculator()
    : calculator_(new Calculator()),
      creditAmount_(1000000),
      months_(12),
      percentage_(10),
      type_(kAnnuity) {}

CreditCalculator::~CreditCalculator() { delete calculator_; }

std::string CreditCalculator::getAnnuityMonthlyPayment() {
  const size_t length = 255;
  char expression[length] = {};
  snprintf(expression, sizeof(expression),
           "%lf*(%lf/1200+%lf/1200/((1+%lf/1200)^%d-1))", creditAmount_,
           percentage_, percentage_, percentage_, months_);
  std::string strExpression(expression);
  calculator_->resetCalculator();
  calculator_->addToInputLine(strExpression);
  double result = calculator_->calculateDoubleResult(0);
  return std::to_string(static_cast<int>(result));
}

std::string CreditCalculator::getDifferentiatedPayment() {
  calculator_->resetCalculator();
  std::string base =
      std::to_string(creditAmount_) + "/" + std::to_string(months_);
  std::string firstPayment = "";
  std::string lastPayment = "";

  for (int i = 1; i <= months_; ++i) {
    calculator_->resetCalculator();
    const size_t length = 255;
    char expression[length] = {};
    snprintf(expression, sizeof(expression), "%s+(%lf-%s*(%d-1))*%lf/(100*12)",
             base.c_str(), creditAmount_, base.c_str(), i, percentage_);
    calculator_->addToInputLine(std::string(expression));
    std::string result = std::to_string(calculator_->calculateDoubleResult(0));
    if (i == 1) firstPayment = result;
    if (i == months_) lastPayment = result;
  }
  calculator_->resetCalculator();
  std::string expression = "0.5*(" + firstPayment + "+" + lastPayment + ")";
  calculator_->addToInputLine(std::string(expression));
  int result = calculator_->calculateDoubleResult(0);
  std::string strResult = std::to_string(result);
  return strResult;
}

std::string CreditCalculator::getAveragePayment() {
  std::string result = "";
  if (type_ == kAnnuity) {
    result = getAnnuityMonthlyPayment();
  } else {
    result = getDifferentiatedPayment();
  }
  return result;
}

std::string CreditCalculator::getOverpayment(
    const std::string& overallPayment) {
  std::string expression = overallPayment + "-" + std::to_string(creditAmount_);
  calculator_->resetCalculator();
  calculator_->addToInputLine(expression);
  int result = calculator_->calculateDoubleResult(0);
  return std::to_string(result);
}

std::string CreditCalculator::getOverallPayment(
    const std::string& averagePayment) {
  std::string expression = averagePayment + "*" + std::to_string(months_);
  calculator_->resetCalculator();
  calculator_->addToInputLine(expression);
  int overallPayment = calculator_->calculateDoubleResult(0);
  return std::to_string(overallPayment);
}

void CreditCalculator::setStrCreditAmount(const std::string& amount) {
  creditAmount_ = std::stod(amount);
}

void CreditCalculator::setStrTime(const std::string& months) {
  months_ = std::stod(months);
}

void CreditCalculator::setStrPercentage(const std::string& percentage) {
  percentage_ = std::stod(percentage);
}

void CreditCalculator::setStrType(const std::string& type) {
  if (type == "Annuity") {
    type_ = kAnnuity;
  } else if (type == "Differentiated") {
    type_ = kDifferentiated;
  }
}

CreditData CreditCalculator::getCreditData() {
  CreditData data;
  std::string averagePayment = getAveragePayment();
  std::string overallPayment = getOverallPayment(averagePayment);
  std::string overpayment = getOverpayment(overallPayment);
  data.setAveragePayment(averagePayment);
  data.setOverallPayment(overallPayment);
  data.setOverpayment(overpayment);
  return data;
}
