#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <iostream>
#include <std/experimental/math/parallel_cpu_engine.hpp>
#include <std/experimental/math/serial_cpu_engine_fwd.hpp>
#include <std/experimental/math/vector.hpp>

namespace math = std::experimental::math;

TEST_CASE("vector: test01: traits", "[vector]")
{
  using vector = math::vector<int>;

  static_assert(std::is_same_v<vector::field_type, double>);
  static_assert(std::is_same_v<vector::engine_type, int>);
  static_assert(vector::is_owning_type::value);
}

TEST_CASE("vector: test02: construction and access", "[vector]")
{
  auto const tolerance = std::numeric_limits<double>::epsilon();
  using vector = math::vector<int>;

  std::size_t size = 10;

  auto v = vector(size);

  for (std::size_t i = 0; i < size; ++i) {
    v(i) = i;
  }

  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(v(i) - i) < tolerance);
  }
}

TEST_CASE("vector: test02: change engine and manipulation", "[vector]")
{
  auto const tolerance = std::numeric_limits<double>::epsilon();
  using vector = math::vector<int>;
  std::size_t size = 10;

  auto w1 = vector(size).change_engine<double>();
  static_assert(std::is_same_v<math::vector<double>, decltype(w1)>);

  auto v2 = vector(size);
  auto w2 = v2.change_engine<double>();
  static_assert(
    std::is_same_v<math::vector_view<double, vector>, decltype(w2)>);

  v2(2) = 3;

  REQUIRE(std::abs(w2(2) - 3) < tolerance);

  w2(2) = 3;

  REQUIRE(std::abs(v2(2) - 3) < tolerance);

  auto const v3 = vector(size);
  auto w3 = v3.change_engine<double>();
  static_assert(
    std::is_same_v<math::vector_view<double, vector const>, decltype(w3)>);
}

TEST_CASE("vector: test03: operators", "[vector]")
{

  auto const tolerance = std::numeric_limits<double>::epsilon();
  using vector = math::vector<math::serial_cpu_engine>;
  static_assert(math::uses_engine_v<math::serial_cpu_engine, vector>);
  static_assert(math::detail::has_engine_type<vector>::value);
  static_assert(
    math::detail::uses_engine<vector, math::serial_cpu_engine>::value);
  std::size_t size = 10;
  auto const w1 = ([size]() {
    auto tmpw1 = vector(size);
    for (std::size_t i = 0; i < size; ++i) {
      tmpw1(i) = i;
    }
    return tmpw1;
  })();

  auto const w2 = ([size]() {
    auto tmpw1 = vector(size);
    for (std::size_t i = 0; i < size; ++i) {
      tmpw1(i) = -static_cast<double>(i);
    }
    return tmpw1;
  })();

  auto const w3 = w1 + w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w3(i)) < tolerance);
  }

  auto const w4 = w1 - w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w4(i) - static_cast<double>(2 * i)) < tolerance);
  }

  auto const w5 = -w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w5(i) - static_cast<double>(i)) < tolerance);
  }
}

TEST_CASE("vector: test04: parallel operators", "[vector]")
{

  auto const tolerance = std::numeric_limits<double>::epsilon();
  using vector = math::vector<math::parallel_cpu_engine>;
  std::size_t size = 10;
  auto const w1 = ([size]() {
    auto tmpw1 = vector(size);
    for (std::size_t i = 0; i < size; ++i) {
      tmpw1(i) = i;
    }
    return tmpw1;
  })();

  auto const w2 = ([size]() {
    auto tmpw1 = vector(size);
    for (std::size_t i = 0; i < size; ++i) {
      tmpw1(i) = -static_cast<double>(i);
    }
    return tmpw1;
  })();

  auto const w3 = w1 + w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w3(i)) < tolerance);
  }

  auto const w4 = w1 - w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w4(i) - static_cast<double>(2 * i)) < tolerance);
  }

  auto const w5 = -w2;
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w5(i) - static_cast<double>(i)) < tolerance);
  }

  auto const w6 = w1.change_engine<math::serial_cpu_engine>()
                  + w2.change_engine<math::serial_cpu_engine>();
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w3(i)) < tolerance);
  }

  auto const w7 = w1.change_engine<math::serial_cpu_engine>()
                  - w2.change_engine<math::serial_cpu_engine>();
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w4(i) - static_cast<double>(2 * i)) < tolerance);
  }

  auto const w8 = -w2.change_engine<math::serial_cpu_engine>();
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w5(i) - static_cast<double>(i)) < tolerance);
  }
}
