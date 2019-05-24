#ifndef STD_EXPERIMENTAL_MATH_TRAITS_HPP
#define STD_EXPERIMENTAL_MATH_TRAITS_HPP

#include <std/experimental/math/detail/traits.hpp>
#include <std/experimental/math/ns.hpp>
#include <type_traits>

namespace MATH_NS {
template <typename T>
struct is_numeric_field : std::false_type {
};

template <>
struct is_numeric_field<double> : std::true_type {
};

template <>
struct is_numeric_field<float> : std::true_type {
};

template <class Tp, class E>
struct uses_engine : public detail::uses_engine<Tp, E> {
};

template <class Tp, class E>
inline constexpr size_t uses_engine_v = uses_engine<Tp, E>::value;

} // namespace MATH_NS

#endif // STD_EXPERIMENTAL_MATH_TRAITS_HPP
