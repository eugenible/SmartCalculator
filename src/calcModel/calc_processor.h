#ifndef CALC_PROCESSOR_H
#define CALC_PROCESSOR_H

#include <deque>

#include "binary_operation.h"
#include "token.h"
#include "valued_token.h"

using namespace s21;

namespace s21 {
class Calculator;
class CalculationProcessor {
 public:
  CalculationProcessor();
  ~CalculationProcessor();
  CalculationProcessor(const CalculationProcessor& other);
  CalculationProcessor& operator=(const CalculationProcessor& other);
  CalculationProcessor(CalculationProcessor&& other);

  double calculate(std::deque<Token*>* rpn, double varValue);
  void resetProcessor();

 private:
  std::deque<Token*>* operations_;
  std::deque<double>* operands_;

  // Methods for private use
  void processIfOperand(Token* token, TokenType type, double varValue);
  bool processIfUnaryOperation(Token* token, TokenType type);
  bool processIfBinaryOperation(Token* token, TokenType type);
};
}  // namespace s21

#endif  // CALC_PROCESSOR_H
