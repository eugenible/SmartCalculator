#include "plot_data.h"

using namespace s21;

PlotData::PlotData()
    : isExpressionValid_(true), xCoords_(), yCoords_(), min_(0), max_(0) {}

PlotData::~PlotData() {
  xCoords_.clear();
  yCoords_.clear();
}

PlotData::PlotData(const PlotData& other)
    : isExpressionValid_(other.isExpressionValid_),
      xCoords_(other.xCoords_),
      yCoords_(other.yCoords_),
      min_(other.min_),
      max_(other.max_) {}

PlotData::PlotData(PlotData&& other)
    : isExpressionValid_(other.isExpressionValid_),
      min_(other.min_),
      max_(other.max_),
      xCoords_(std::move(other.xCoords_)),
      yCoords_(std::move(other.yCoords_)) {}

bool PlotData::isValidExpression() { return isExpressionValid_; }

std::vector<double>& PlotData::getXCoords() { return xCoords_; }

std::vector<double>& PlotData::getYCoords() { return yCoords_; }

double PlotData::getMin() { return min_; }

double PlotData::getMax() { return max_; }

void PlotData::setValidExpression(bool expression) {
  isExpressionValid_ = expression;
}

void PlotData::setXCoords(const std::vector<double>& xCoords) {
  xCoords_ = xCoords;
}

void PlotData::setYCoords(const std::vector<double>& yCoords) {
  yCoords_ = yCoords;
}

void PlotData::setMin(double min) { min_ = min; }

void PlotData::setMax(double max) { max_ = max; }
