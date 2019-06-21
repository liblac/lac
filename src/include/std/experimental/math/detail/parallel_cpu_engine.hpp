#ifndef STD_EXPERIMENTAL_MATH_DETAIL_PARALLEL_CPU_ENGINE_HPP
#define STD_EXPERIMENTAL_MATH_DETAIL_PARALLEL_CPU_ENGINE_HPP

#include <std/experimental/math/parallel_cpu_engine_fwd.hpp>
#include <std/experimental/math/vector.hpp>

namespace std::experimental::math::detail {
template <typename T, typename U>
struct parallel_addition_traits {
  using result_type = vector<parallel_cpu_engine>;
};

template <typename T, typename U>
using parallel_addition_traits_r =
  typename parallel_addition_traits<T, U>::result_type;

template <typename T, typename U>
struct parallel_addition_engine {
  auto operator()(T&& t, U&& u) const -> parallel_addition_traits_r<T, U>
  {
    auto const size = t.size();
    auto result = parallel_addition_traits_r<T, U>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = t(i) + u(i);
    }
    return result;
  }
};

template <typename T, typename U>
struct parallel_subtraction_traits {
  using result_type = vector<parallel_cpu_engine>;
};

template <typename T, typename U>
using parallel_subtraction_traits_r =
  typename parallel_subtraction_traits<T, U>::result_type;

template <typename T, typename U>
struct parallel_subtraction_engine {
  auto operator()(T&& t, U&& u) const -> parallel_subtraction_traits_r<T, U>
  {
    auto const size = t.size();
    auto result = parallel_subtraction_traits_r<T, U>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = t(i) - u(i);
    }
    return result;
  }
};

template <typename T>
struct parallel_negation_traits {
  using result_type = vector<parallel_cpu_engine>;
};

template <typename T>
using parallel_negation_traits_r =
  typename parallel_negation_traits<T>::result_type;

template <typename T>
struct parallel_negation_engine {
  auto operator()(T&& t) const -> parallel_negation_traits_r<T>
  {
    auto const size = t.size();
    auto result = parallel_negation_traits_r<T>(size);
    for (std::size_t i = 0; i < size; ++i) {
      result(i) = -t(i);
    }
    return result;
  }
};

} // namespace std::experimental::math::detail

#endif // STD_EXPERIMENTAL_MATH_DETAIL_PARALLEL_CPU_ENGINE_HPP
