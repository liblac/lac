#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
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
