#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <std/experimental/math/vector.hpp>
#include <std/experimental/math/vector_view.hpp>

namespace math = std::experimental::math;

TEST_CASE("vector_view: test01: traits", "[vector_view]")
{
  using vector = math::vector<double>;
  using vector_view = math::vector_view<int, vector>;

  static_assert(std::is_same_v<vector::engine_type, double>);
  static_assert(std::is_same_v<vector_view::engine_type, int>);
}

TEST_CASE("vector_view: test01: construction", "[vector_view]")
{
  auto const tolerance = std::numeric_limits<double>::epsilon();
  using vector = math::vector<double>;
  using vector_view = math::vector_view<int, vector>;
  using vector_const_view = math::vector_view<int, vector const>;

  std::size_t const size = 10;

  auto const v1 = vector(size);
  [[maybe_unused]] auto w1 = vector_const_view(v1);

  auto v2 = vector(size);
  auto w2 = vector_view(v2);

  for (std::size_t i = 0; i < size; ++i) {
    v2(i) = i;
  }

  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w2(i) - i) < tolerance);
  }

  for (std::size_t i = 0; i < size; ++i) {
    w2(i) = size - i;
  }

  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(v2(i) - size + i) < tolerance);
  }

  auto const w2c = vector_const_view(v2);
  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(w2c(i) - size + i) < tolerance);
  }
}
