#ifndef LAC_DETAIL_TRAITS_HPP
#define LAC_DETAIL_TRAITS_HPP

#include <type_traits>

namespace lac::detail {

template <typename T>
constexpr bool if_float_field()
{
  if constexpr (std::is_arithmetic_v<T>) {
    return true;
  }

  return false;
}
} // namespace lac::detail

#endif // LAC_DETAIL_TRAITS_HPP
