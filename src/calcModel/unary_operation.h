#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "token.h"

namespace s21 {
class UnaryOperation : public Token {
 public:
  UnaryOperation() : Token() {}
  ~UnaryOperation() {}
  UnaryOperation(TokenType type, Priority priority, const std::string &strVal)
      : Token(type, priority, strVal) {}

  //  Operation performing
  virtual double apply(double o1) = 0;
};
}  // namespace s21

#endif  // UNARY_OPERATION_H
