#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include "calculator.h"
#include "credit_data.h"

namespace s21 {

enum CreditType { kAnnuity, kDifferentiated };

class CreditCalculator {
 public:
  CreditCalculator();
  ~CreditCalculator();

  std::string getOverpayment(const std::string& overallPayment);
  std::string getOverallPayment(const std::string& averagePayment);
  std::string getAveragePayment();

  void setStrCreditAmount(const std::string& amount);
  void setStrTime(const std::string& months);
  void setStrPercentage(const std::string& percentage);
  void setStrType(const std::string& type);
  CreditData getCreditData();

 private:
  Calculator* calculator_;

  double creditAmount_;
  int months_;
  double percentage_;
  CreditType type_;

  std::string getAnnuityMonthlyPayment();
  std::string getDifferentiatedPayment();

  // Копирование этих элементов не предусмотрено, функции сделаны приватными, в
  // случае попытки копирования компилятор покажет ошибку
  CreditCalculator(const CreditCalculator& other);
  CreditCalculator& operator=(const CreditCalculator& other);
};
}  // namespace s21

#endif  // CREDIT_CALC_H