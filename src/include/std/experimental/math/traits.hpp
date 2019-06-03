#ifndef STD_EXPERIMENTAL_MATH_TRAITS_HPP
#define STD_EXPERIMENTAL_MATH_TRAITS_HPP

#include <std/experimental/math/detail/traits.hpp>
#include <type_traits>

namespace std::experimental::math {
template <typename T>
struct is_numeric_field : std::false_type {
};

template <>
struct is_numeric_field<double> : std::true_type {
};

template <>
struct is_numeric_field<float> : std::true_type {
};

template <class T>
inline constexpr bool is_numeric_field_v = is_numeric_field<T>::value;

template <class Tp>
struct is_engine_aware : public detail::has_engine_type<Tp> {
};

template <class Tp>
inline constexpr bool is_engine_aware_v = is_engine_aware<Tp>::value;

template <typename E, typename... T>
struct uses_engine : std::conjunction<detail::uses_engine<T, E>...> {
};

template <class E, class... Tp>
inline constexpr bool uses_engine_v = uses_engine<E, Tp...>::value;

} // namespace std::experimental::math

#endif // STD_EXPERIMENTAL_MATH_TRAITS_HPP
