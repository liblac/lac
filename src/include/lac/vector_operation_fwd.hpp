#ifndef LAC_VECTOR_OPERATION_FWD_HPP
#define LAC_VECTOR_OPERATION_FWD_HPP

#include <lac/traits.hpp>
#include <type_traits>

namespace lac {
template <typename A,
          typename RT = negation_trait_r<A>,
          typename = std::enable_if_t<lac::is_vector_storage_v<A>>>
auto operator-(A const& va) -> RT;

template <typename A,
          typename B,
          typename RT = addition_trait_r<A, B>,
          typename = std::enable_if_t<
            lac::is_vector_storage_v<A> and lac::is_vector_storage_v<B>>>
auto operator+(A const& va, B const& vb) -> RT;

template <typename A,
          typename B,
          typename RT = subtraction_trait_r<A, B>,
          typename = std::enable_if_t<
            lac::is_vector_storage_v<A> and lac::is_vector_storage_v<B>>>
auto operator-(A const& va, B const& vb) -> RT;
} // namespace lac

#endif // LAC_VECTOR_OPERATION_FWD_HPP
