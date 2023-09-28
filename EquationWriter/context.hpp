#ifndef EQUATION_WRITER_CONTEXT_HPP_
#define EQUATION_WRITER_CONTEXT_HPP_

#include <string>

#include "variable.hpp"

namespace EquationWriter {

class Context {
 public:
  Context() = default;
  ~Context() = default;

  Variable CreateVariable() { return Variable(num_variables_++); }
  Variable CreateVariable(std::string name) {
    return Variable(num_variables_++, name);
  }
  size_t GetNumVariables() const { return num_variables_; }

 private:
  size_t num_variables_ = 0;
};

}  // namespace EquationWriter

#endif  // EQUATION_WRITER_CONTEXT_HPP_