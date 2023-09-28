#ifndef EQUATION_WRITER_LINEAR_SYSTEM_HPP_
#define EQUATION_WRITER_LINEAR_SYSTEM_HPP_

#include <iostream>
#include <vector>

#include "context.hpp"
#include "equation.hpp"

namespace EquationWriter {

class LinearSystem {
 public:
  LinearSystem() = default;
  ~LinearSystem() = default;

  void AddEquation(const Equation &equation) { equations_.push_back(equation); }

  template <typename Matrix>
  void FillMatrix(Matrix &m) const {
    for (size_t i = 0; i < equations_.size(); ++i)
      equations_[i].FillMatrix(m, i);
  }

  template <typename Column>
  void FillRightSide(Column &rhs) const {
    for (size_t i = 0; i < equations_.size(); ++i)
      equations_[i].FillRightSide(rhs, i);
  }

  std::pair<size_t, size_t> GetMatrixDimension(const Context &c) const {
    return std::make_pair(equations_.size(), c.GetNumVariables());
  }

  size_t GetNumEquations() const { return equations_.size(); }

  friend std::ostream &operator<<(std::ostream &os, const LinearSystem &s);

 private:
  std::vector<Equation> equations_;
};

inline std::ostream &operator<<(std::ostream &os, const LinearSystem &s) {
  bool first = true;
  for (const auto &equation : s.equations_) {
    if (first) {
      first = false;
      os << equation;
      continue;
    }
    os << std::endl << equation;
  }
  return os;
}

}  // namespace EquationWriter

#endif  // EQUATION_WRITER_LINEAR_SYSTEM_HPP_