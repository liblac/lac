#ifndef STD_EXPERIMENTAL_MATH_SERIAL_CPU_ENGINE_FWD_HPP
#define STD_EXPERIMENTAL_MATH_SERIAL_CPU_ENGINE_FWD_HPP

#include <std/experimental/math/traits.hpp>
#include <std/experimental/math/vector.hpp>

namespace std::experimental::math {
struct serial_cpu_engine {
};

template <typename T, typename U>
struct addition_traits {
  using result_type = vector<serial_cpu_engine>;
};

template <typename T, typename U>
using addition_traits_r = typename addition_traits<T, U>::result_type;

template <typename T, typename U>
struct addition_engine {
  auto operator()(T&& t, U&& u) const -> addition_traits_r<T, U>
  {
    auto const size = t.size();
    auto result = addition_traits_r<T, U>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = t(i) + u(i);
    }
    return result;
  }
};

template <typename T,
          typename U,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            serial_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>,
            std::remove_cv_t<std::remove_reference_t<U>>>>>
auto operator+(T&& t, U&& u) -> addition_traits_r<T&&, U&&>
{
  auto constexpr ae = addition_engine<T, U>();
  return ae(std::forward<T>(t), std::forward<U>(u));
}

template <typename T, typename U>
struct subtraction_traits {
  using result_type = vector<serial_cpu_engine>;
};

template <typename T, typename U>
using subtraction_traits_r = typename subtraction_traits<T, U>::result_type;

template <typename T, typename U>
struct subtraction_engine {
  auto operator()(T&& t, U&& u) const -> subtraction_traits_r<T, U>
  {
    auto const size = t.size();
    auto result = subtraction_traits_r<T, U>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = t(i) - u(i);
    }
    return result;
  }
};

template <typename T,
          typename U,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            serial_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>,
            std::remove_cv_t<std::remove_reference_t<U>>>>>
auto operator-(T&& t, U&& u) -> subtraction_traits_r<T&&, U&&>
{
  auto constexpr se = subtraction_engine<T, U>();
  return se(std::forward<T>(t), std::forward<U>(u));
}

template <typename T>
struct negation_traits {
  using result_type = vector<serial_cpu_engine>;
};

template <typename T>
using negation_traits_r = typename negation_traits<T>::result_type;

template <typename T>
struct negation_engine {
  auto operator()(T&& t) const -> negation_traits_r<T>
  {
    auto const size = t.size();
    auto result = negation_traits_r<T>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = -t(i);
    }
    return result;
  }
};

template <typename T,
          typename = std::enable_if_t<std::experimental::math::uses_engine_v<
            serial_cpu_engine,
            std::remove_cv_t<std::remove_reference_t<T>>>>>
auto operator-(T&& t) -> negation_traits_r<T&&>
{
  auto constexpr ne = negation_engine<T>();
  return ne(std::forward<T>(t));
}

} // namespace std::experimental::math

#endif // STD_EXPERIMENTAL_MATH_SERIAL_CPU_ENGINE_FWD_HPP
