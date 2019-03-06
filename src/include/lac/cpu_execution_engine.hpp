#ifndef LAC_CPU_EXECUTION_ENGINE_HPP
#define LAC_CPU_EXECUTION_ENGINE_HPP

#include <cstdint>
#include <lac/execution_engine_fwd.hpp>
#include <lac/execution_policy.hpp>

namespace lac {
template <>
struct negation_engine<cpu_execution_policy> {

  template <typename T, typename RT>
  auto operator()(T const& t) const -> RT
  {
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = -t(i);
    }
    return result;
  }
};

template <>
struct addition_engine<cpu_execution_policy> {
  template <typename T, typename U, typename RT>
  auto operator()(T const& t, U const& u) const -> RT
  {
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = t(i) + u(i);
    }
    return result;
  }
};

template <>
struct subtraction_engine<cpu_execution_policy> {
  template <typename T, typename U, typename RT>
  auto operator()(T const& t, U const& u) const -> RT
  {
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = t(i) - u(i);
    }
    return result;
  }
};

} // namespace lac

#endif // LAC_CPU_EXECUTION_ENGINE_HPP
