#ifndef PLOT_BUILDER_H
#define PLOT_BUILDER_H

#include <map>
#include <vector>

#include "plot_data.h"

namespace s21 {

class Calculator;

class PlotBuilder {
 public:
  PlotBuilder();
  explicit PlotBuilder(Calculator *calculator);
  ~PlotBuilder();
  PlotBuilder(const PlotBuilder &other);

  PlotData getCoordinates();
  bool increaseScale();
  bool decreaseScale();

 private:
  Calculator *calculator_;
  std::size_t maxScale_;
  std::size_t minScale_;
  std::size_t scale_;

  std::map<std::size_t, double> xRange_ = {
      std::make_pair(0, 1),      std::make_pair(1, 5),
      std::make_pair(2, 20),     std::make_pair(3, 100),
      std::make_pair(4, 500),    std::make_pair(5, 5000),
      std::make_pair(6, 100000), std::make_pair(7, 1000000)};
  ;
  std::map<std::size_t, double> step_ = {
      std::make_pair(0, 0.001), std::make_pair(1, 0.005),
      std::make_pair(2, 0.01),  std::make_pair(3, 0.05),
      std::make_pair(4, 0.25),  std::make_pair(5, 2.5),
      std::make_pair(6, 50),    std::make_pair(7, 500),
  };

  bool calculateCoordinates(std::vector<double> *xCoords,
                            std::vector<double> *yCoords);
};
}  // namespace s21

#endif  // PLOT_BUILDER_H
