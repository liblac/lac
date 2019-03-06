#ifndef LAC_STATIC_VECTOR_HPP
#define LAC_STATIC_VECTOR_HPP

#include <array>
#include <lac/traits.hpp>

namespace lac {
template <typename EP, typename F, std::int64_t N>
class static_vector;

template <typename EP, typename F, std::int64_t N>
struct is_vector_storage<static_vector<EP, F, N>> : std::true_type {
};

template <typename EP, typename F, std::int64_t N>
class static_vector {

private:
  static_assert(lac::is_float_field_v<F>);
  static_assert(N >= 1);

public:
  using field_type = F;
  using is_resizable_type = std::false_type;
  using index_type = std::int64_t;
  using offset_type = index_type;
  using size_type = index_type;
  using execution_policy = EP;

private:
  static constexpr size_type size_ = N;
  using storage_type = std::array<field_type, size_>;

public:
  using iterator = typename storage_type::iterator;
  using const_iterator = typename storage_type::const_iterator;

public:
  static_vector() = default;
  static_vector(static_vector&&) = default;
  static_vector(static_vector const&) = default;

  static_vector& operator=(static_vector&&) = default;
  static_vector& operator=(static_vector const&) = default;

public:
  constexpr auto size() const noexcept -> size_type const&;
  constexpr auto capacity() const noexcept -> size_type const&;

  constexpr auto operator()(index_type i) const -> field_type const&;
  constexpr auto operator()(index_type i) -> field_type&;

  constexpr auto begin() const noexcept -> const_iterator;
  constexpr auto begin() noexcept -> iterator;

  constexpr auto end() const noexcept -> const_iterator;
  constexpr auto end() noexcept -> iterator;

private:
  std::array<field_type, size_> x_;
  offset_type offset_{0};
};

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::capacity() const noexcept
  -> size_type const&
{
  return size_;
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::size() const noexcept
  -> size_type const&
{
  return size_;
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::operator()(index_type i) const
  -> field_type const&
{
  return x_[i];
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::operator()(index_type i) -> field_type&
{
  return x_[i];
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::begin() const noexcept -> const_iterator
{
  return std::begin(x_);
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::begin() noexcept -> iterator
{
  return std::begin(x_);
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::end() const noexcept -> const_iterator
{
  return std::end(x_);
}

template <typename EP, typename F, std::int64_t N>
constexpr auto static_vector<EP, F, N>::end() noexcept -> iterator
{
  return std::end(x_);
}

} // namespace lac

#endif // LAC_STATIC_VECTOR_HPP
