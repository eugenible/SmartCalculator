#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cmath>
#include <string>

#include "binary_operation.h"
#include "token.h"
#include "unary_operation.h"

namespace s21 {
class Sum : public BinaryOperation {
 public:
  Sum() : BinaryOperation(kBinaryOperator, kLow, "+") {}
  ~Sum() {}
  virtual double apply(double o1, double o2) override { return o1 + o2; }
};

class Subtraction : public BinaryOperation {
 public:
  Subtraction() : BinaryOperation(kBinaryOperator, kLow, "-") {}
  ~Subtraction() {}
  virtual double apply(double o1, double o2) override { return o1 - o2; }
};

class UnaryPlus : public UnaryOperation {
 public:
  UnaryPlus() : UnaryOperation(kUnaryOperator, kHighest, "+") {}
  ~UnaryPlus() {}
  virtual double apply(double o1) override { return 1.0 * o1; }
};

class UnaryMinus : public UnaryOperation {
 public:
  UnaryMinus() : UnaryOperation(kUnaryOperator, kHighest, "-") {}
  ~UnaryMinus() {}
  virtual double apply(double o1) override { return -1.0 * o1; }
};

class Mul : public BinaryOperation {
 public:
  Mul() : BinaryOperation(kBinaryOperator, kMedium, "*") {}
  ~Mul() {}
  virtual double apply(double o1, double o2) override { return o1 * o2; }
};

class Division : public BinaryOperation {
 public:
  Division() : BinaryOperation(kBinaryOperator, kMedium, "/") {}
  ~Division() {}
  virtual double apply(double o1, double o2) override { return o1 / o2; }
};

class Power : public BinaryOperation {
 public:
  Power() : BinaryOperation(kBinaryOperator, kHigh, "^") {}
  ~Power() {}
  virtual double apply(double o1, double o2) override { return pow(o1, o2); }
};

class Modulo : public BinaryOperation {
 public:
  Modulo() : BinaryOperation(kBinaryOperator, kMedium, "mod") {}
  ~Modulo() {}
  virtual double apply(double o1, double o2) override { return fmod(o1, o2); }
};

}  // namespace s21

#endif  // OPERATIONS_H