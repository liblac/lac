#ifndef STD_EXPERIMENTAL_MATH_VECTOR_VIEW_HPP
#define STD_EXPERIMENTAL_MATH_VECTOR_VIEW_HPP

#include <std/experimental/math/vector_view_fwd.hpp>
#include <type_traits>

namespace std::experimental::math::detail {
}
namespace std::experimental::math {

template <typename E, typename R>
class vector_view {
public:
  using field_type = typename R::field_type;
  using engine_type = E;
  using index_type = typename R::index_type;
  using size_type = typename R::size_type;

  using is_owning_type = std::false_type;
  using owning_type = R;

public:
  vector_view() = default;
  vector_view(vector_view&&) = default;
  vector_view(vector_view const&) = default;
  vector_view& operator=(vector_view&&) = default;
  vector_view& operator=(vector_view const&) = default;

  explicit vector_view(owning_type& owning_value);

public:
  auto size() const noexcept -> size_type;

  auto operator()(index_type i) const
    -> std::conditional_t<std::is_const_v<R>,
                          typename R::field_type const,
                          typename R::field_type>&;

  auto operator()(index_type i)
    -> std::conditional_t<std::is_const_v<R>,
                          typename R::field_type const,
                          typename R::field_type>&;

  template <typename NE>
  auto change_engine() const -> vector_view<NE, owning_type>;

private:
  owning_type* owner_ptr_;
};

template <typename E, typename R>
vector_view<E, R>::vector_view(owning_type& owning_value)
: owner_ptr_(&owning_value)
{
  static_assert(not std::is_rvalue_reference_v<owning_type>);
}

template <typename E, typename R>
auto vector_view<E, R>::size() const noexcept -> size_type
{
  return owner_ptr_->size();
}

template <typename E, typename R>
auto vector_view<E, R>::operator()(index_type i) const
  -> std::conditional_t<std::is_const_v<R>,
                        typename R::field_type const,
                        typename R::field_type>&
{
  return (*owner_ptr_)(i);
}

template <typename E, typename R>
auto vector_view<E, R>::operator()(index_type i)
  -> std::conditional_t<std::is_const_v<R>,
                        typename R::field_type const,
                        typename R::field_type>&
{
  return (*owner_ptr_)(i);
}

template <typename E, typename R>
template <typename NE>
auto vector_view<E, R>::change_engine() const -> vector_view<NE, owning_type>
{
  return vector_view<NE, owning_type>(*owner_ptr_);
}
} // namespace std::experimental::math

#endif // STD_EXPERIMENTAL_MATH_VECTOR_VIEW_HPP
