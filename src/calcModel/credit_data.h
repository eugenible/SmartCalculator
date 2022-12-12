#ifndef CREDIT_DATA_H
#define CREDIT_DATA_H

#include <string>

namespace s21 {
class CreditData {
 public:
  CreditData();
  ~CreditData();
  CreditData(const CreditData& other);
  CreditData& operator=(const CreditData& other);

  void setOverallPayment(const std::string& value);
  void setOverpayment(const std::string& value);
  void setAveragePayment(const std::string& value);

  std::string getOverallPayment();
  std::string getOverpayment();
  std::string getAveragePayment();

 private:
  std::string strOverallPayment_;
  std::string strOverpayment_;
  std::string strAveragePayment_;
};
}  // namespace s21

#endif  // CREDIT_DATA_H
