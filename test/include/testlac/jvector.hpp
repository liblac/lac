#ifndef TESTLAC_JVECTOR_HPP
#define TESTLAC_JVECTOR_HPP

#include <array>
#include <cstdint>
#include <lac/traits.hpp>

namespace testlac {
template <typename EP>
class jvector;
}

namespace lac {
template <typename EP>
struct is_vector_storage<testlac::jvector<EP>> : std::true_type {
};

template <typename EP>
struct addition_trait<testlac::jvector<EP>, testlac::jvector<EP>> {
  using result_type = testlac::jvector<EP>;
};

template <typename EP>
struct subtraction_trait<testlac::jvector<EP>, testlac::jvector<EP>> {
  using result_type = testlac::jvector<EP>;
};
} // namespace lac

namespace testlac {
template <typename EP>
class jvector;

template <typename EP>
class jvector {

public:
  using field_type = double;
  using is_resizable_type = std::false_type;
  using index_type = std::int64_t;
  using offset_type = index_type;
  using size_type = index_type;
  using execution_policy = EP;

private:
  static constexpr size_type size_ = 3;
  using storage_type = std::array<field_type, size_>;

public:
  using iterator = typename storage_type::iterator;
  using const_iterator = typename storage_type::const_iterator;

public:
  jvector() = default;
  jvector(jvector&&) = default;
  jvector(jvector const&) = default;

  jvector& operator=(jvector&&) = default;
  jvector& operator=(jvector const&) = default;

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

template <typename EP>
constexpr auto jvector<EP>::capacity() const noexcept -> size_type const&
{
  return size_;
}

template <typename EP>
constexpr auto jvector<EP>::size() const noexcept -> size_type const&
{
  return size_;
}

template <typename EP>
constexpr auto jvector<EP>::operator()(index_type i) const -> field_type const&
{
  return x_[i];
}

template <typename EP>
constexpr auto jvector<EP>::operator()(index_type i) -> field_type&
{
  return x_[i];
}

template <typename EP>
constexpr auto jvector<EP>::begin() const noexcept -> const_iterator
{
  return std::begin(x_);
}

template <typename EP>
constexpr auto jvector<EP>::begin() noexcept -> iterator
{
  return std::begin(x_);
}

template <typename EP>
constexpr auto jvector<EP>::end() const noexcept -> const_iterator
{
  return std::end(x_);
}

template <typename EP>
constexpr auto jvector<EP>::end() noexcept -> iterator
{
  return std::end(x_);
}

} // namespace testlac

#endif // TESTLAC_JVECTOR_HPP
