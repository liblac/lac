#define CATCH_CONFIG_FAST_COMPILE
#include <cassert>
#include <catch2/catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <lac/execution_policy.hpp>
#include <lac/static_vector.hpp>
#include <lac/vector_operation.hpp>
#include <limits>

namespace testlac {
struct verbose_policy {
};
} // namespace testlac

namespace lac {
template <>
struct negation_engine<testlac::verbose_policy> {

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
struct addition_engine<testlac::verbose_policy> {
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
struct subtraction_engine<testlac::verbose_policy> {
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

using vec3 = lac::static_vector<lac::cpu_execution_policy, double, 3>;
using rvec3 = lac::static_vector<testlac::verbose_policy, double, 3>;
constexpr auto tolerance = std::numeric_limits<double>::epsilon();

TEST_CASE("static_vector : type_check", "[static_vector]")
{
  static_assert(lac::is_vector_storage_v<vec3>);
}

TEST_CASE("static_vector : construction", "[static_vector]")
{
  auto static_vector = vec3();

  static_vector(0) = 2;
  static_vector(1) = 3;
  static_vector(2) = 5;

  REQUIRE(static_vector.capacity() == 3);
  REQUIRE(static_vector.size() == 3);
  REQUIRE(std::abs(static_vector(0) - 2) < tolerance);
  REQUIRE(std::abs(static_vector(1) - 3) < tolerance);
  REQUIRE(std::abs(static_vector(2) - 5) < tolerance);
}

TEST_CASE("static_vector : iterator based access", "[static_vector]")
{

  auto static_vector = vec3();

  static_vector(0) = 2;
  static_vector(1) = 3;
  static_vector(2) = 5;

  for (auto& a : static_vector) {
    a *= 2;
  }

  REQUIRE(std::abs(static_vector(0) - 4) < tolerance);
  REQUIRE(std::abs(static_vector(1) - 6) < tolerance);
  REQUIRE(std::abs(static_vector(2) - 10) < tolerance);
}

TEST_CASE("static_vector : negation", "[static_vector]")
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

TEST_CASE("static_vector : addition", "[static_vector]")
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

TEST_CASE("static_vector : subtraction", "[static_vector]")
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

TEST_CASE("static_vector: verbose negation", "[static_vector]")
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

TEST_CASE("static_vector: verbose addition", "[static_vector]")
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

TEST_CASE("static_vector: verbose subtraction", "[static_vector]")
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
