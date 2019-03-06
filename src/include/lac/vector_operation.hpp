#ifndef LAC_VECTOR_OPERATION_HPP
#define LAC_VECTOR_OPERATION_HPP

#include <lac/cpu_execution_engine.hpp>
#include <lac/vector_operation_fwd.hpp>

namespace lac {
template <typename A, typename RT, typename EE>
auto operator-(A const& a) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto ne = negation_engine<EP>();
  return ne.template operator()<A, RT>(a);
}

template <typename A, typename B, typename RT, typename EE>
auto operator+(A const& a, B const& b) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto ae = addition_engine<EP>();
  return ae.template operator()<A, B, RT>(a, b);
}

template <typename A, typename B, typename RT, typename EE>
auto operator-(A const& a, B const& b) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto se = subtraction_engine<EP>();
  return se.template operator()<A, B, RT>(a, b);
}
} // namespace lac

#endif // LAC_VECTOR_OPERATION_HPP
