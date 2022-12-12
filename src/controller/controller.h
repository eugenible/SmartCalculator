#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "../calcModel/calculator.h"
#include "../calcModel/credit_calc.h"
#include "../calcModel/credit_data.h"

namespace s21 {

class CreditCalculator;

class Controller {
 public:
  Controller();
  ~Controller();
  Controller(Controller&& other);

  void addToInputLine(const std::string& addition);
  void setVarValue(const std::string& strVarValue);
  void calculate();
  std::string getInputLine();
  std::string getOutputLine();
  void clearInputLine();
  void deleteElement();
  bool increaseScale();
  bool decreaseScale();
  PlotData getPlotCoordinates();
  CreditData getCreditData();
  void setStrCreditAmount(const std::string& amount);
  void setStrTime(const std::string& months);
  void setStrPercentage(const std::string& percentage);
  void setStrType(const std::string& type);

 private:
  Calculator* calculator_;
  CreditCalculator* credit_;

  // Копирование этих элементов не предусмотрено, функции сделаны приватными, в
  // случае попытки копирования компилятор покажет ошибку
  Controller(const Controller& other);
  Controller& operator=(const Controller& other);
};
}  // namespace s21

#endif  // CONTROLLER_H
