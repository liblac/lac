#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <std/experimental/math/serial_cpu.hpp>
#include <std/experimental/math/vector.hpp>

namespace math = std::experimental::math;

TEST_CASE("vector: test01: type_check", "[vector]")
{
}

TEST_CASE("vector: test02: construction and operator[]", "[vector]")
{
  static constexpr auto tolerance = std::numeric_limits<double>::epsilon();
  using engine_type = math::serial_cpu_engine;
  using vector_type = math::vector<engine_type>;

  std::size_t const size = 20;
  auto v = vector_type(size);

  REQUIRE(v.size() == size);

  for (std::size_t i = 0; i < size; ++i) {
    v(i) = i;
  }

  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(v(i) - i * 1.0) < tolerance);
  }
}

TEST_CASE("vector: test02: change_engine", "[vector]")
{
  static constexpr auto tolerance = std::numeric_limits<double>::epsilon();
  using engine_type = math::serial_cpu_engine;
  using vector_type = math::vector<engine_type>;

  std::size_t const size = 20;
  auto v = vector_type(size);

  REQUIRE(v.size() == size);

  for (std::size_t i = 0; i < size; ++i) {
    v(i) = i;
  }

  auto const new_vector = v.change_engine<bool>();

  for (std::size_t i = 0; i < size; ++i) {
    REQUIRE(std::abs(new_vector(i) - i * 1.0) < tolerance);
  }
}
