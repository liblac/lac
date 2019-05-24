#ifndef STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP
#define STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP

#include <std/experimental/math/ns.hpp>
#include <type_traits>

namespace MATH_NS::detail {
template <class Tp>
struct has_engine_type {
private:
  struct two {
    char lx;
    char lxx;
  };

  template <class Up>
  static two test(...);

  template <class Up>
  static char test(typename Up::engine_type* = 0);

public:
  static const bool value = (sizeof(test<Tp>(0)) == 1);
};

template <class Tp, class E, bool = has_engine_type<Tp>::value>
struct uses_engine
: public integral_constant<bool,
                           is_convertible<E, typename Tp::engine_type>::value> {
};
} // namespace MATH_NS::detail

#endif // STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP
