#include "calc_processor.h"

#include <iostream>

#include "binary_operation.h"
#include "deque"
#include "token.h"
#include "unary_operation.h"
#include "valued_token.h"

using namespace s21;

CalculationProcessor::CalculationProcessor() : operations_(), operands_() {
  operations_ = new std::deque<Token *>();
  operands_ = new std::deque<double>();
}

void CalculationProcessor::resetProcessor() {
  if (operations_) operations_->clear();
  if (operands_) operands_->clear();
}

CalculationProcessor &CalculationProcessor::operator=(
    const CalculationProcessor &other) {
  if (this != &other) {
    operations_ = new std::deque<Token *>(*(other.operations_));
    operands_ = new std::deque<double>(*(other.operands_));
  }
  return *this;
}

CalculationProcessor::~CalculationProcessor() {
  delete operations_;
  delete operands_;
}

CalculationProcessor::CalculationProcessor(const CalculationProcessor &other) {
  operations_ = new std::deque<Token *>(*(other.operations_));
  operands_ = new std::deque<double>(*(other.operands_));
}

CalculationProcessor::CalculationProcessor(CalculationProcessor &&other) {
  operations_ = other.operations_;
  operands_ = other.operands_;
  other.operations_ = nullptr;
  other.operands_ = nullptr;
}

void CalculationProcessor::processIfOperand(Token *token, TokenType type,
                                            double varValue) {
  if (type == kNumber || type == kVariable) {
    ValuedToken<double> *number = static_cast<ValuedToken<double> *>(token);
    double valueForPush = (type == kNumber) ? number->getValue() : varValue;
    operands_->push_back(valueForPush);
  }
}

bool CalculationProcessor::processIfUnaryOperation(Token *token,
                                                   TokenType type) {
  if (type == kUnaryOperator || type == kFunction) {
    if (operands_->empty()) return false;
    double operand = operands_->back();
    operands_->pop_back();
    double result = (static_cast<UnaryOperation *>(token))->apply(operand);
    operands_->push_back(result);
  }
  return true;
}

bool CalculationProcessor::processIfBinaryOperation(Token *token,
                                                    TokenType type) {
  if (type == kBinaryOperator) {
    if (operands_->size() < 2) return false;
    double o1 = operands_->back();
    operands_->pop_back();
    double o2 = operands_->back();
    operands_->pop_back();
    double result = (static_cast<BinaryOperation *>(token))->apply(o2, o1);
    operands_->push_back(result);
  }
  return true;
}

double CalculationProcessor::calculate(std::deque<Token *> *rpn,
                                       double varValue) {
  Token *token = nullptr;
  TokenType type;
  double result = 0;
  for (size_t i = 0; i < rpn->size(); ++i) {
    token = rpn->at(i);
    type = token->getType();
    processIfOperand(token, type, varValue);
    if (!processIfUnaryOperation(token, type) ||
        !processIfBinaryOperation(token, type)) {
      throw std::invalid_argument("Invalid input");
    }
  }

  if (operands_->size() != 1) {
    throw std::invalid_argument("Invalid input");
  } else {
    result = operands_->back();
    operands_->pop_back();
  }
  return result;
}
