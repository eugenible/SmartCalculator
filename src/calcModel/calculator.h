#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <deque>
#include <string>

#include "calc_processor.h"
#include "plot_builder.h"
#include "plot_data.h"
#include "request.h"
#include "token.h"

namespace s21 {

class PlotBuilder;

class Calculator {
 public:
  // Constructors and destructors
  Calculator();
  ~Calculator();

  // Setters
  void resetCalculator();
  void addToInputLine(const std::string& addition);
  void deleteLastElement();
  void setVarValueByString(const std::string& strValValue);

  // Getters
  std::string getOutputLine();
  std::string getInputLine();

  // Рассчитывает выражение
  void calculate();
  double calculateDoubleResult(double variable);

  // Plot Building
  PlotData getPlotCoordinates();
  bool increaseScale();
  bool decreaseScale();

  // Checks if request is valid
  bool isRequestValid();

 private:
  Request request_;
  CalculationProcessor processor_;
  PlotBuilder builder_;

  double result_;
  double varValue_;
  std::string inputLine_;
  std::string outputLine_;

  // Calculator is not supposed to be copyable
  Calculator(const Calculator& other);

  // Methods for inner implementation
  void passLineToRequest(const std::string& line);
  void resetComponents();
  void refreshRequest();
  std::deque<Token*>* getNotation();
  void setVariableValue(double varValue);
};

}  // namespace s21

#endif  // CALCULATOR_H
