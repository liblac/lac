#ifndef TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP
#define TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP

#include <std/experimental/math/traits.hpp>
#include <type_traits>

namespace math = std::experimental::math;

namespace teststd::experimental::math {

struct traits_test02_struct_01 {
  using engine_type = int;
};

struct traits_test02_struct_02 {
};

struct traits_test02_struct_03a {
  using engine_type = int;
};

struct traits_test02_struct_03b {
  using engine_type = int;
};

struct traits_test02_struct_04a {
  using engine_type = int;
};

struct traits_test02_struct_04b {
  using engine_type = double;
};

struct traits_test03_struct_01 {
  using is_owning_type = std::true_type;
};

struct traits_test03_struct_02 {
  using is_owning_type = std::false_type;
};

template <typename... T>
struct traits_test04_traits_03 {
  using result_type = std::conditional_t<
    std::experimental::math::is_consuming_owning_type_v<T...>,
    int,
    double>;
};

template <typename T, typename U>
auto traits_test04_function_04([[maybe_unused]] T&& t, [[maybe_unused]] U&& u)
  -> typename traits_test04_traits_03<T&&, U&&>::result_type
{
  using result_type = typename traits_test04_traits_03<T&&, U&&>::result_type;

  return result_type(0);
}

struct traits_test04_struct_01 {
  using is_owning_type = std::true_type;
};

struct traits_test04_struct_02 {
  using is_owning_type = std::false_type;
};

} // namespace teststd::experimental::math

#endif // TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP
