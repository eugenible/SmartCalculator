#include "controller.h"

#include <iostream>
#include <string>
#include <vector>

#include "../calcModel/calculator.h"

using namespace s21;

Controller::Controller()
    : calculator_(new Calculator()), credit_(new CreditCalculator()) {}

Controller::~Controller() {
  delete calculator_;
  delete credit_;
}

Controller::Controller(Controller&& other) {
  calculator_ = other.calculator_;
  credit_ = other.credit_;
  other.calculator_ = nullptr;
  other.credit_ = nullptr;
}

void Controller::addToInputLine(const std::string& addition) {
  calculator_->addToInputLine(addition);
}

void Controller::setVarValue(const std::string& strVarValue) {
  calculator_->setVarValueByString(strVarValue);
}

void Controller::calculate() { calculator_->calculate(); }

std::string Controller::getInputLine() { return calculator_->getInputLine(); }

std::string Controller::getOutputLine() { return calculator_->getOutputLine(); }

void Controller::clearInputLine() { calculator_->resetCalculator(); }

void Controller::deleteElement() { calculator_->deleteLastElement(); }

bool Controller::increaseScale() { return calculator_->increaseScale(); }

bool Controller::decreaseScale() { return calculator_->decreaseScale(); }

// Plot building

PlotData Controller::getPlotCoordinates() {
  return calculator_->getPlotCoordinates();
}

// Credit data operating

CreditData Controller::getCreditData() { return credit_->getCreditData(); }

void Controller::setStrCreditAmount(const std::string& amount) {
  credit_->setStrCreditAmount(amount);
}

void Controller::setStrTime(const std::string& months) {
  credit_->setStrTime(months);
}

void Controller::setStrPercentage(const std::string& percentage) {
  credit_->setStrPercentage(percentage);
}

void Controller::setStrType(const std::string& type) {
  credit_->setStrType(type);
}
