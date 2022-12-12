#include "credit_data.h"

#include <string>

using namespace s21;

CreditData::CreditData()
    : strOverallPayment_("0"), strOverpayment_("0"), strAveragePayment_("0") {}

CreditData::~CreditData() {}

void CreditData::setOverallPayment(const std::string& value) {
  strOverallPayment_ = value;
}

void CreditData::setOverpayment(const std::string& value) {
  strOverpayment_ = value;
}
void CreditData::setAveragePayment(const std::string& value) {
  strAveragePayment_ = value;
}

CreditData::CreditData(const CreditData& other)
    : strOverallPayment_(other.strOverallPayment_),
      strAveragePayment_(other.strAveragePayment_),
      strOverpayment_(other.strOverpayment_) {}

CreditData& CreditData::operator=(const CreditData& other) {
  if (this != &other) {
    strAveragePayment_ = other.strAveragePayment_;
    strOverallPayment_ = other.strOverallPayment_;
    strOverpayment_ = other.strOverpayment_;
  }
  return *this;
}

std::string CreditData::getOverallPayment() { return strOverallPayment_; }

std::string CreditData::getOverpayment() { return strOverpayment_; }

std::string CreditData::getAveragePayment() { return strAveragePayment_; }
