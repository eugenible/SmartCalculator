#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <string>

#include "binary_operation.h"
#include "token.h"
#include "unary_operation.h"

namespace s21 {
class Cosine : public UnaryOperation {
 public:
  Cosine() : UnaryOperation(kFunction, kHighest, "cos") {}
  ~Cosine() {}
  virtual double apply(double o1) override { return cos(o1); }
};

class Sine : public UnaryOperation {
 public:
  Sine() : UnaryOperation(kFunction, kHighest, "sin") {}
  ~Sine() {}
  virtual double apply(double o1) override { return sin(o1); }
};

class Tangent : public UnaryOperation {
 public:
  Tangent() : UnaryOperation(kFunction, kHighest, "tan") {}
  ~Tangent() {}
  virtual double apply(double o1) override { return tan(o1); }
};

class ArcCosine : public UnaryOperation {
 public:
  ArcCosine() : UnaryOperation(kFunction, kHighest, "acos") {}
  ~ArcCosine() {}
  virtual double apply(double o1) override { return acos(o1); }
};

class ArcSine : public UnaryOperation {
 public:
  ArcSine() : UnaryOperation(kFunction, kHighest, "asin") {}
  ~ArcSine() {}
  virtual double apply(double o1) override { return asin(o1); }
};

class ArcTangent : public UnaryOperation {
 public:
  ArcTangent() : UnaryOperation(kFunction, kHighest, "atan") {}
  ~ArcTangent() {}
  virtual double apply(double o1) override { return atan(o1); }
};

class SquareRoot : public UnaryOperation {
 public:
  SquareRoot() : UnaryOperation(kFunction, kHighest, "sqrt") {}
  ~SquareRoot() {}
  virtual double apply(double o1) override { return sqrt(o1); }
};

class LogN : public UnaryOperation {
 public:
  LogN() : UnaryOperation(kFunction, kHighest, "ln") {}
  ~LogN() {}
  virtual double apply(double o1) override { return log(o1); }
};

class Log : public UnaryOperation {
 public:
  Log() : UnaryOperation(kFunction, kHighest, "log") {}
  ~Log() {}
  virtual double apply(double o1) override { return log10(o1); }
};

}  // namespace s21

#endif  // FUNCTIONS_H