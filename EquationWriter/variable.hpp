#ifndef EQUATION_WRITER_VARIABLE_HPP_
#define EQUATION_WRITER_VARIABLE_HPP_

#include <string>

namespace EquationWriter {

class Variable {
 public:
  Variable(size_t id, std::string name) : id_(id), name_(name) {}
  explicit Variable(size_t id) : id_(id) {}
  Variable() = delete;
  ~Variable() = default;

  size_t GetID() const { return id_; }
  std::string GetName() const { return name_; }

  bool operator<(const Variable &other) const { return id_ < other.id_; }

 private:
  size_t id_ = 0;
  std::string name_ = "";
};

inline std::ostream &operator<<(std::ostream &os, const Variable &v) {
  if (v.GetName().empty()) return os << "x_" << v.GetID();
  return os << v.GetName();
}

}  // namespace EquationWriter

#endif  // EQUATION_WRITER_VARIABLE_HPP_