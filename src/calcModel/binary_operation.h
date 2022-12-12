#ifndef BINARY_OPERATION_H
#define BINARY_OPERATION_H

#include <string>

#include "token.h"

namespace s21 {
class BinaryOperation : public Token {
 public:
  BinaryOperation() : Token() {}
  ~BinaryOperation() {}
  BinaryOperation(TokenType type, Priority priority, const std::string& strVal)
      : Token(type, priority, strVal) {}

  // Operation performing
  virtual double apply(double o1, double o2) = 0;
};
}  // namespace s21

#endif  // BINARY_OPERATION_H