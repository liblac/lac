#ifndef STD_EXPERIMENTAL_MATH_VECTOR_HPP
#define STD_EXPERIMENTAL_MATH_VECTOR_HPP

#include <cstdint>
#include <std/experimental/math/ns.hpp>
#include <type_traits>
#include <vector>

namespace MATH_NS {

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

  vector(size_type size);

public:
  auto size() const noexcept -> size_type;

  auto operator()(index_type i) const -> field_type const&;
  auto operator()(index_type i) -> field_type&;

  template <typename NE>
  auto change_engine() -> vector<NE>;

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
auto vector<E>::change_engine() -> vector<NE>
{
  auto result = vector<NE>();
  result.storage_ = std::move(storage_);
  return result;
}
} // namespace MATH_NS

#endif // STD_EXPERIMENTAL_MATH_VECTOR_HPP
