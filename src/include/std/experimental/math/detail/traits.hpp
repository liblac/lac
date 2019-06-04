#ifndef STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP
#define STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP

#include <type_traits>

namespace std::experimental::math::detail {
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
  static char test(typename Up::engine_type* = nullptr);

public:
  static const bool value = (sizeof(test<Tp>(nullptr)) == 1);
};

template <class Tp, class E, bool = has_engine_type<Tp>::value>
struct uses_engine
: public bool_constant<is_convertible<E, typename Tp::engine_type>::value> {
};

template <class Tp, class E>
struct uses_engine<Tp, E, false> : public false_type {
};

template <class Tp>
struct has_owning_type {
private:
  struct two {
    char lx;
    char lxx;
  };

  template <class Up>
  static two test(...);

  template <class Up>
  static char test(typename Up::is_owning_type* = nullptr);

public:
  static const bool value = (sizeof(test<Tp>(nullptr)) == 1);
};

template <class Tp, bool = has_owning_type<Tp>::value>
struct is_owning_type
: public bool_constant<
    is_convertible<std::true_type, typename Tp::is_owning_type>::value> {
};

template <class Tp>
struct is_owning_type<Tp, false> : std::false_type {
};

template <class Tp>
inline constexpr bool is_owning_type_v = is_owning_type<Tp>::value;

template <class Tp>
struct is_consuming_owning_type
: std::bool_constant<is_owning_type_v<std::remove_cv_t<std::remove_reference_t<
                       Tp>>> and std::is_rvalue_reference_v<Tp>> {
};

} // namespace std::experimental::math::detail

#endif // STD_EXPERIMENTAL_MATH_DETAIL_TRAITS_HPP
