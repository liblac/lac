#ifndef STD_EXPERIMENTAL_MATH_PARALLEL_CPU_ENGINE_HPP
#define STD_EXPERIMENTAL_MATH_PARALLEL_CPU_ENGINE_HPP

#include <iostream>
#include <std/experimental/math/detail/parallel_cpu_engine.hpp>
#include <std/experimental/math/parallel_cpu_engine_fwd.hpp>
#include <std/experimental/math/traits.hpp>
#include <std/experimental/math/vector.hpp>

namespace std::experimental::math {
struct parallel_cpu_engine {
};

template <typename T,
          typename U,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            parallel_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>,
            std::remove_cv_t<std::remove_reference_t<U>>>>>
auto operator+(T&& t, U&& u) -> detail::parallel_addition_traits_r<T&&, U&&>
{
  std::cout << "Parallel Algorithm \n";
  auto constexpr ae = detail::parallel_addition_engine<T, U>();
  return ae(std::forward<T>(t), std::forward<U>(u));
}

template <typename T,
          typename U,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            parallel_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>,
            std::remove_cv_t<std::remove_reference_t<U>>>>>
auto operator-(T&& t, U&& u) -> detail::parallel_subtraction_traits_r<T&&, U&&>
{
  std::cout << "Parallel Algorithm \n";
  auto constexpr se = detail::parallel_subtraction_engine<T, U>();
  return se(std::forward<T>(t), std::forward<U>(u));
}

template <typename T,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            parallel_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>>>>
auto operator-(T&& t) -> detail::parallel_negation_traits_r<T&&>
{
  std::cout << "Parallel Algorithm \n";
  auto constexpr ne = detail::parallel_negation_engine<T>();
  return ne(std::forward<T>(t));
}

} // namespace std::experimental::math

#endif // STD_EXPERIMENTAL_MATH_PARALLEL_CPU_ENGINE_HPP
