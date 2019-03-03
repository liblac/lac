#ifndef LAC_DETAIL_MAKE_ARRAY_HPP
#define LAC_DETAIL_MAKE_ARRAY_HPP

#include <array>
#include <type_traits>

namespace lac::detail::make_array_detail {
template <class>
struct is_ref_wrapper : std::false_type {
};
template <class T>
struct is_ref_wrapper<std::reference_wrapper<T>> : std::true_type {
};

template <class T>
using not_ref_wrapper = std::negation<is_ref_wrapper<std::decay_t<T>>>;

template <class D, class...>
struct return_type_helper {
  using type = D;
};
template <class... Types>
struct return_type_helper<void, Types...> : std::common_type<Types...> {
  static_assert(std::conjunction_v<not_ref_wrapper<Types>...>,
                "Types cannot contain reference_wrappers when D is void");
};

template <class D, class... Types>
using return_type = std::array<typename return_type_helper<D, Types...>::type,
                               sizeof...(Types)>;

} // namespace lac::detail::make_array_detail

namespace lac::detail {
template <class D = void, class... Types>
constexpr auto make_array(Types&&... t)
  -> make_array_detail::return_type<D, Types...>
{
  return {std::forward<Types>(t)...};
}
} // namespace lac::detail

#endif // LAC_DETAIL_MAKE_ARRAY_HPP
