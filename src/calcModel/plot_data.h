#ifndef PLOT_DATA_H
#define PLOT_DATA_H

#include <vector>

namespace s21 {

class PlotData {
 public:
  PlotData();
  ~PlotData();
  PlotData(const PlotData& other);
  PlotData(PlotData&& other);

  // Getters
  bool isValidExpression();
  std::vector<double>& getXCoords();
  std::vector<double>& getYCoords();
  double getMin();
  double getMax();

  // Setters
  void setValidExpression(bool expression);
  void setXCoords(const std::vector<double>& xCoords);
  void setYCoords(const std::vector<double>& yCoords);
  void setMin(double min);
  void setMax(double max);

 private:
  bool isExpressionValid_;
  std::vector<double> xCoords_;
  std::vector<double> yCoords_;
  double min_, max_;
};
}  // namespace s21

#endif  // PLOT_DATA_H