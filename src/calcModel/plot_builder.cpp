#include "plot_builder.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "calculator.h"

using namespace s21;

PlotBuilder::PlotBuilder()
    : calculator_(nullptr), maxScale_(7), minScale_(0), scale_(1) {}

PlotBuilder::PlotBuilder(Calculator *calculator)
    : calculator_(calculator), maxScale_(7), minScale_(0), scale_(1) {}

PlotBuilder::PlotBuilder(const PlotBuilder &other)
    : calculator_(other.calculator_),
      maxScale_(7),
      minScale_(0),
      scale_(1),
      xRange_(other.xRange_),
      step_(other.step_) {}

PlotBuilder::~PlotBuilder() {}

bool PlotBuilder::increaseScale() {
  if (scale_ >= maxScale_) return false;
  scale_++;
  return true;
}

bool PlotBuilder::decreaseScale() {
  if (scale_ <= minScale_) return false;
  scale_--;
  return true;
}

bool PlotBuilder::calculateCoordinates(std::vector<double> *xCoords,
                                       std::vector<double> *yCoords) {
  try {
    double maxRange = xRange_.at(scale_);
    double step = step_.at(scale_);
    for (double x = -2 * maxRange; x <= 2 * maxRange; x += step) {
      double result = calculator_->calculateDoubleResult(x);
      xCoords->push_back(x);
      yCoords->push_back(result);
    }
  } catch (std::invalid_argument &exc) {
    return false;
  }
  return true;
}

PlotData PlotBuilder::getCoordinates() {
  std::vector<double> xCoords;
  std::vector<double> yCoords;
  PlotData data;

  if (!calculator_->isRequestValid()) {
    data.setValidExpression(false);
    return data;
  }

  if (!calculateCoordinates(&xCoords, &yCoords)) {
    data.setValidExpression(false);
    return data;
  }

  data.setMin(xCoords.at(0));
  data.setMax(xCoords.at(xCoords.size() - 1));
  data.setXCoords(xCoords);
  data.setYCoords(yCoords);
  return data;
}
