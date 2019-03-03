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
} // namespace lac

#endif // LAC_TRAITS_HPP
