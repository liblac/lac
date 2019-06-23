#ifndef LAC_VECTOR_HPP
#define LAC_VECTOR_HPP

#include <std/experimental/math/vector_view.hpp>
#include <vector>

namespace lac {
template <typename E>
class vector {
public:
  using field_type = double;
  using engine_type = E;
  using index_type = std::size_t;
  using size_type = std::size_t;
  using is_owning_type = std::true_type;

private:
  using storage_type = std::vector<field_type>;

public:
  vector() = default;
  vector(vector&&) = default;
  vector(vector const&) = default;
  vector& operator=(vector&&) = default;
  vector& operator=(vector const&) = default;

  explicit vector(size_type size);

public:
  auto size() const noexcept -> size_type;

  auto operator()(index_type i) const -> field_type const&;
  auto operator()(index_type i) -> field_type&;

  template <typename NE>
  auto change_engine() && -> vector<NE>;

  template <typename NE>
  auto change_engine() & -> std::experimental::math::vector_view<NE, vector<E>>;

  template <typename NE>
  auto change_engine()
    const& -> std::experimental::math::vector_view<NE, vector<E> const>;

private:
  storage_type storage_;

public:
  template <class NE>
  friend class vector;
};

template <typename E>
vector<E>::vector(size_type size) : storage_(size, 0)
{
}

template <typename E>
auto vector<E>::size() const noexcept -> size_type
{
  return storage_.size();
}

template <typename E>
auto vector<E>::operator()(index_type i) const -> field_type const&
{
  return storage_[i];
}

template <typename E>
auto vector<E>::operator()(index_type i) -> field_type&
{
  return storage_[i];
}

template <typename E>
template <typename NE>
auto vector<E>::change_engine() && -> vector<NE>
{
  auto result = vector<NE>();
  result.storage_ = std::move(storage_);
  return result;
}

template <typename E>
template <typename NE>
auto vector<E>::change_engine()
  const& -> std::experimental::math::vector_view<NE, vector<E> const>
{
  return std::experimental::math::vector_view<NE, vector<E> const>(*this);
}

template <typename E>
template <typename NE>
auto vector<
  E>::change_engine() & -> std::experimental::math::vector_view<NE, vector<E>>
{
  return std::experimental::math::vector_view<NE, vector<E>>(*this);
}
} // namespace lac

#endif // LAC_VECTOR_HPP
