#ifndef EQUATION_WRITER_EXPRESSION_HPP_
#define EQUATION_WRITER_EXPRESSION_HPP_

#include <map>

#include "variable.hpp"

namespace EquationWriter {

class Expression {
 public:
  Expression() = default;
  ~Expression() = default;

  void AddTerm(double coefficient, Variable variable) {
    if (coefficients_.count(variable) == 0) coefficients_[variable] = 0.0;
    coefficients_[variable] += coefficient;
  }

  template <typename Matrix, typename... FixedIndices>
  void FillMatrix(Matrix &m, FixedIndices... fixed_indices) const {
    for (const auto &term : coefficients_)
      m(fixed_indices..., term.first.GetID()) = term.second;
  }

  Expression operator*(double constant) const {
    Expression result = *this;
    for (auto &term : result.coefficients_) term.second *= constant;
    return result;
  }

  Expression operator+(const Expression &other) const {
    Expression result = *this;
    for (const auto &term : other.coefficients_)
      result.AddTerm(term.second, term.first);
    return result;
  }

  Expression operator-(const Expression &other) const {
    Expression result = *this;
    for (const auto &term : other.coefficients_)
      result.AddTerm(-term.second, term.first);
    return result;
  }

  Expression operator-() const {
    Expression result = *this;
    for (auto &term : result.coefficients_) term.second = -term.second;
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Expression &m);

 private:
  std::map<Variable, double> coefficients_;
};

inline std::ostream &operator<<(std::ostream &os, const Expression &m) {
  bool first = true;
  for (const auto &term : m.coefficients_) {
    if (first)
      first = false;
    else
      os << " + ";

    if (term.second != 1.0) os << term.second << " * ";
    os << term.first;
  }
  return os;
}

}  // namespace EquationWriter

#endif  // EQUATION_WRITER_EXPRESSION_HPP_