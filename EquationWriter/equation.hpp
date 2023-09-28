#ifndef EQUATION_WRITER_EQUATION_HPP_
#define EQUATION_WRITER_EQUATION_HPP_

#include <limits>

#include "expression.hpp"
#include "variable.hpp"

namespace EquationWriter {

class Equation {
 public:
  Equation() = default;
  Equation(double constant) : rhs_(-constant) {}
  Equation(const Variable &variable) : Equation(1.0, variable) {}
  Equation(double coefficient, Variable variable) : rhs_(0) {
    AddTerm(coefficient, variable);
  }
  ~Equation() = default;

  void AddTerm(double coefficient, Variable variable) {
    lhs_.AddTerm(coefficient, variable);
  }

  template <typename Matrix, typename... FixedIndices>
  void FillMatrix(Matrix &m, FixedIndices... fixed_indices) const {
    lhs_.FillMatrix(m, fixed_indices...);
  }

  template <typename Column, typename... FixedIndices>
  void FillRightSide(Column &rhs, FixedIndices... fixed_indices) const {
    rhs(fixed_indices...) = rhs_;
  }

  Equation operator+(double constant) const {
    Equation result = *this;
    result.rhs_ -= constant;
    return result;
  }

  Equation operator*(double constant) const {
    Equation result;
    result.rhs_ = rhs_ * constant;
    result.lhs_ = lhs_ * constant;
    return result;
  }

  Equation operator+(const Equation &other) const {
    Equation result = *this;
    result.lhs_ = lhs_ + other.lhs_;
    result.rhs_ = rhs_ + other.rhs_;
    return result;
  }

  Equation operator-(const Equation &other) const {
    Equation result = *this;
    result.lhs_ = lhs_ - other.lhs_;
    result.rhs_ = rhs_ - other.rhs_;
    return result;
  }

  Equation operator-() const {
    Equation result = *this;
    result.lhs_ = -lhs_;
    result.rhs_ = -rhs_;
    return result;
  }

  Equation operator==(const Equation &other) const { return *this - other; }

  friend std::ostream &operator<<(std::ostream &os, const Equation &m);

 private:
  Expression lhs_;
  double rhs_;
};

inline Equation operator+(double constant, const Equation &equation) {
  return equation + constant;
}

inline Equation operator+(const Variable &variable, const Equation &equation) {
  return equation + variable;
}

inline Equation operator+(double constant, Variable &variable) {
  return Equation(constant) + variable;
}

inline Equation operator-(const Variable &variable, const Equation &equation) {
  return -equation + variable;
}

inline Equation operator-(double constant, const Equation &equation) {
  return -equation + constant;
}

inline Equation operator*(double coefficient, const Variable &variable) {
  return Equation(coefficient, variable);
}

inline Equation operator*(const Variable &variable, double coefficient) {
  return Equation(coefficient, variable);
}

inline std::ostream &operator<<(std::ostream &os, const Equation &m) {
  return os << m.lhs_ << " = " << m.rhs_;
}

}  // namespace EquationWriter

#endif  // EQUATION_WRITER_EQUATION_HPP_