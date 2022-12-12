#include "calculator.h"

#include <iostream>

using namespace s21;

Calculator::Calculator()
    : request_(),
      processor_(),
      result_(0),
      inputLine_(""),
      outputLine_(""),
      varValue_(0),
      builder_(this) {
  addToInputLine("0");
  calculate();
}

Calculator::~Calculator() {}

std::deque<Token*>* Calculator::getNotation() {
  if (!request_.isRequestValid()) {
    throw std::invalid_argument("Invalid input");
  }
  return request_.getNotation();
}

bool Calculator::isRequestValid() { return request_.isRequestValid(); }

void Calculator::resetComponents() {
  processor_.resetProcessor();
  request_.resetRequest();
}

double Calculator::calculateDoubleResult(double variable) {
  double result = 0;
  std::deque<Token*>* notation = getNotation();
  result = processor_.calculate(notation, variable);
  return result;
}

void Calculator::calculate() {
  try {
    result_ = calculateDoubleResult(varValue_);
    outputLine_ = std::to_string(result_);
  } catch (std::invalid_argument& exc) {
    outputLine_ = "Неверное выражение!";
    processor_.resetProcessor();
  }
}

void Calculator::resetCalculator() {
  inputLine_ = "0";
  resetComponents();
  refreshRequest();
  calculate();
}

void Calculator::deleteLastElement() {
  processor_.resetProcessor();
  if (inputLine_ == "0") return;

  int length = request_.getLastElementLength();
  inputLine_ = inputLine_.substr(0, inputLine_.length() - length);
  if (inputLine_ == "") {
    resetCalculator();
    return;
  }
  refreshRequest();
}

std::string Calculator::getOutputLine() {
  if (outputLine_ == "Неверное выражение!") return outputLine_;
  const size_t outputLength = 255;
  char formatted[outputLength] = {};
  snprintf(formatted, sizeof(formatted), "%.7lf", result_);
  return formatted;
}

void Calculator::addToInputLine(const std::string& addition) {
  if (inputLine_ == "0" && addition != ".") inputLine_ = "";
  inputLine_ += addition;
  refreshRequest();
}

void Calculator::refreshRequest() {
  if (inputLine_ != request_.getLine()) {
    request_.resetRequest();
    request_.setLine(inputLine_);
    request_.processLine();
  }
}

void Calculator::setVariableValue(double varValue) { varValue_ = varValue; }

std::string Calculator::getInputLine() { return inputLine_; }

void Calculator::setVarValueByString(const std::string& strVarValue) {
  char* end;
  double result = strtod(strVarValue.c_str(), &end);
  if (end == strVarValue.c_str() || *end != '\0') return;
  setVariableValue(result);
}

PlotData Calculator::getPlotCoordinates() { return builder_.getCoordinates(); }

bool Calculator::increaseScale() { return builder_.increaseScale(); }

bool Calculator::decreaseScale() { return builder_.decreaseScale(); }
