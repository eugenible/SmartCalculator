#include <iostream>

#include "calcModel/calculator.h"
#include "calcModel/credit_calc.h"
#include "calcModel/credit_data.h"
#include "gtest/gtest.h"

TEST(CalculationTest, calculations) {
  Calculator c;

  c.addToInputLine("1.6+(-4512.124)*sin(144.8)");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "-1274.5408174");
  c.resetCalculator();

  c.addToInputLine("2^(-3)");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "0.1250000");
  c.resetCalculator();

  c.addToInputLine("sqrt(89)-tan(56)");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "10.0452548");
  c.resetCalculator();

  c.addToInputLine("asin(1)-56^log(23)+acos(0)/(1*sqrt(34))");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "-238.3505758");
  c.resetCalculator();

  c.addToInputLine("log(ln(10000))sqrt");
  c.deleteLastElement();
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "0.9642757");
  c.resetCalculator();

  c.addToInputLine("cos(2)+atan(100)");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "1.1446498");
  c.resetCalculator();

  c.addToInputLine("10mod4");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "2.0000000");
  c.resetCalculator();

  c.addToInputLine("+10+9");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "19.0000000");
  c.resetCalculator();

  c.addToInputLine("-10+x");
  c.setVarValueByString("100");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "90.0000000");
  c.resetCalculator();

  c.addToInputLine("+10+9");
  c.deleteLastElement();
  c.deleteLastElement();
  c.deleteLastElement();
  c.deleteLastElement();
  c.deleteLastElement();
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "0.0000000");
  c.resetCalculator();
}

TEST(CalculationTest, exceptions) {
  CalculationProcessor cp;
  CalculationProcessor copiedCp(cp);
  CalculationProcessor movedCp = std::move(cp);

  Calculator c;

  c.addToInputLine("-10+");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("10/");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("10(20(30))");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("10(20(30)))");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("()");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("10**20");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("200x");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine("x+(1())");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  EXPECT_EQ(c.isRequestValid(), false);
  EXPECT_EQ(c.getInputLine(), "x+(1())");
  c.resetCalculator();

  c.addToInputLine("200xty");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();

  c.addToInputLine(")5(");
  c.calculate();
  EXPECT_EQ(c.getOutputLine(), "Неверное выражение!");
  c.resetCalculator();
}

TEST(CalculationTest, credit) {
  CreditCalculator c;
  c.setStrCreditAmount("1000000");
  c.setStrPercentage("10");
  c.setStrTime("12");
  c.setStrType("Annuity");

  CreditData cd = c.getCreditData();

  EXPECT_EQ(cd.getAveragePayment(), "87915");
  EXPECT_EQ(cd.getOverallPayment(), "1054980");
  EXPECT_EQ(cd.getOverpayment(), "54980");

  c.setStrType("Differentiated");

  cd = c.getCreditData();
  EXPECT_EQ(cd.getAveragePayment(), "87847");
  EXPECT_EQ(cd.getOverallPayment(), "1054164");
  EXPECT_EQ(cd.getOverpayment(), "54164");

  CalculationProcessor cp;
  CalculationProcessor cp2;
  cp2 = cp;
}

TEST(CalculationTest, plotting) {
  Calculator c;
  c.addToInputLine("10mod4");
  PlotData pd = c.getPlotCoordinates();
  c.increaseScale();
  c.decreaseScale();
  EXPECT_EQ(pd.getYCoords().at(0), 2);
  EXPECT_EQ(pd.getXCoords().at(0), -10);

  c.resetCalculator();
  c.addToInputLine("10modzz4");
  PlotData pd2 = c.getPlotCoordinates();

  PlotBuilder pb;
  PlotBuilder pb2(pb);
  PlotData pd3;
  PlotData pd4(pd3);
  PlotData pd5 = std::move(pd4);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
