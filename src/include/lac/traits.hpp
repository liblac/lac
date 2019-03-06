#ifndef LAC_TRAITS_HPP
#define LAC_TRAITS_HPP

#include <lac/detail/traits.hpp>
#include <type_traits>

namespace lac {
template <typename T>
struct is_float_field : std::bool_constant<detail::if_float_field<T>()> {
};

template <class T>
inline constexpr bool is_float_field_v = is_float_field<T>::value;

template <typename T>
struct is_vector_storage : std::false_type {
};

template <class T>
inline constexpr bool is_vector_storage_v = is_vector_storage<T>::value;

template <typename A, typename B>
struct addition_trait;

template <typename A, typename B>
struct subtraction_trait;

template <typename T>
struct negation_trait {
  using result_type = T;
};

template <class T>
using negation_trait_r = typename negation_trait<T>::result_type;

template <class T, class U>
using addition_trait_r = typename addition_trait<T, U>::result_type;

template <class T, class U>
using subtraction_trait_r = typename subtraction_trait<T, U>::result_type;
} // namespace lac

#endif // LAC_TRAITS_HPP
