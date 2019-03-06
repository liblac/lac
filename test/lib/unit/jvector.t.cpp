#define CATCH_CONFIG_FAST_COMPILE
#include <cassert>
#include <catch2/catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <lac/cpu_execution_engine.hpp>
#include <lac/execution_policy.hpp>
#include <lac/vector_operation.hpp>
#include <limits>
#include <testlac/jvector.hpp>

namespace randomns {
struct verbose_policy {
};

template <typename A,
          typename RT = lac::negation_trait_r<A>,
          typename = std::enable_if_t<lac::is_vector_storage_v<A>>>
auto operator-(A const& va) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto ne = lac::negation_engine<EP>();
  return ne.template operator()<A, RT>(va);
}

template <typename A,
          typename B,
          typename RT = lac::addition_trait_r<A, B>,
          typename = std::enable_if_t<
            lac::is_vector_storage_v<A> and lac::is_vector_storage_v<B>>>
auto operator+(A const& va, B const& vb) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto ae = lac::addition_engine<EP>();
  return ae.template operator()<A, B, RT>(va, vb);
}

template <typename A,
          typename B,
          typename RT = lac::subtraction_trait_r<A, B>,
          typename = std::enable_if_t<
            lac::is_vector_storage_v<A> and lac::is_vector_storage_v<B>>>
auto operator-(A const& va, B const& vb) -> RT
{
  using EP = typename A::execution_policy;
  constexpr auto se = lac::subtraction_engine<EP>();
  return se.template operator()<A, B, RT>(va, vb);
}

} // namespace randomns

namespace lac {
template <>
struct negation_engine<randomns::verbose_policy> {

  template <typename T, typename RT>
  auto operator()(T const& t) const -> RT
  {
    std::cout << "Negation" << std::endl;
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = -t(i);
    }
    return result;
  }
};

template <>
struct addition_engine<randomns::verbose_policy> {
  template <typename T, typename U, typename RT>
  auto operator()(T const& t, U const& u) const -> RT
  {
    std::cout << "Addition" << std::endl;
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = t(i) + u(i);
    }
    return result;
  }
};

template <>
struct subtraction_engine<randomns::verbose_policy> {
  template <typename T, typename U, typename RT>
  auto operator()(T const& t, U const& u) const -> RT
  {
    std::cout << "Subtraction" << std::endl;
    RT result;
    for (std::int64_t i = 0; i < t.size(); ++i) {
      result(i) = t(i) - u(i);
    }
    return result;
  }
};

} // namespace lac

using vec3 = testlac::jvector<lac::cpu_execution_policy>;
using rvec3 = testlac::jvector<randomns::verbose_policy>;
constexpr auto tolerance = std::numeric_limits<double>::epsilon();

TEST_CASE("jvector : type_check", "[jvector]")
{
  static_assert(lac::is_vector_storage_v<vec3>);
}

TEST_CASE("jvector : construction", "[jvector]")
{
  auto jvector = vec3();

  jvector(0) = 2;
  jvector(1) = 3;
  jvector(2) = 5;

  REQUIRE(jvector.capacity() == 3);
  REQUIRE(jvector.size() == 3);
  REQUIRE(std::abs(jvector(0) - 2) < tolerance);
  REQUIRE(std::abs(jvector(1) - 3) < tolerance);
  REQUIRE(std::abs(jvector(2) - 5) < tolerance);
}

TEST_CASE("jvector : iterator based access", "[jvector]")
{

  auto jvector = vec3();

  jvector(0) = 2;
  jvector(1) = 3;
  jvector(2) = 5;

  for (auto& a : jvector) {
    a *= 2;
  }

  REQUIRE(std::abs(jvector(0) - 4) < tolerance);
  REQUIRE(std::abs(jvector(1) - 6) < tolerance);
  REQUIRE(std::abs(jvector(2) - 10) < tolerance);
}

TEST_CASE("jvector : negation", "[jvector]")
{
  auto va = vec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto const vb = -va;

  REQUIRE(std::abs(vb(0) + 2) < tolerance);
  REQUIRE(std::abs(vb(1) + 3) < tolerance);
  REQUIRE(std::abs(vb(2) + 5) < tolerance);
}

TEST_CASE("jvector : addition", "[jvector]")
{
  auto va = vec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto vb = vec3();
  vb(0) = 3;
  vb(1) = 5;
  vb(2) = 7;

  auto const vc = va + vb;

  REQUIRE(std::abs(vc(0) - 5) < tolerance);
  REQUIRE(std::abs(vc(1) - 8) < tolerance);
  REQUIRE(std::abs(vc(2) - 12) < tolerance);
}

TEST_CASE("jvector : subtraction", "[jvector]")
{
  auto va = vec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto vb = vec3();
  vb(0) = 3;
  vb(1) = 5;
  vb(2) = 7;

  auto const vc = vb - va;

  REQUIRE(std::abs(vc(0) - 1) < tolerance);
  REQUIRE(std::abs(vc(1) - 2) < tolerance);
  REQUIRE(std::abs(vc(2) - 2) < tolerance);
}

TEST_CASE("jvector: verbose negation", "[jvector]")
{
  auto va = rvec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto const vb = -va;

  REQUIRE(std::abs(vb(0) + 2) < tolerance);
  REQUIRE(std::abs(vb(1) + 3) < tolerance);
  REQUIRE(std::abs(vb(2) + 5) < tolerance);
}

TEST_CASE("jvector: verbose addition", "[jvector]")
{
  auto va = rvec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto vb = rvec3();
  vb(0) = 3;
  vb(1) = 5;
  vb(2) = 7;

  auto const vc = va + vb;

  REQUIRE(std::abs(vc(0) - 5) < tolerance);
  REQUIRE(std::abs(vc(1) - 8) < tolerance);
  REQUIRE(std::abs(vc(2) - 12) < tolerance);
}

TEST_CASE("jvector: verbose subtraction", "[jvector]")
{
  auto va = rvec3();
  va(0) = 2;
  va(1) = 3;
  va(2) = 5;

  auto vb = rvec3();
  vb(0) = 3;
  vb(1) = 5;
  vb(2) = 7;

  auto const vc = vb - va;

  REQUIRE(std::abs(vc(0) - 1) < tolerance);
  REQUIRE(std::abs(vc(1) - 2) < tolerance);
  REQUIRE(std::abs(vc(2) - 2) < tolerance);
}
