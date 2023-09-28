#include <iostream>

#include "Eigen/Dense"

#include "linear_system.hpp"
#include "equation.hpp"
#include "context.hpp"

int main() {
  using namespace EquationWriter;

  Context c;
  Variable x = c.CreateVariable("x");
  Variable y = c.CreateVariable("y");
  Variable z = c.CreateVariable("z");

  Equation eq1 = 2 * x + 3 * y == 4.0;
  Equation eq2 = 3 * x  == 5 - 4 * y - 10 + x;
  Equation eq3 = 1 + z - 4 * x + 5 * y + 2 == 6;

  LinearSystem system;
  system.AddEquation(eq1);
  system.AddEquation(eq2);
  system.AddEquation(eq3);

  auto system_size = system.GetMatrixDimension(c);
  Eigen::MatrixXd m(system_size.first, system_size.second);
  Eigen::VectorXd rhs(system_size.first);

  system.FillMatrix(m);
  system.FillRightSide(rhs);

  std::cout << "System:" << std::endl;
  std::cout << system << std::endl;
  std::cout << "Matrix:" << std::endl;
  std::cout << m << std::endl;
  std::cout << "Right side:" << std::endl;
  std::cout << rhs << std::endl;
}