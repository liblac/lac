#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <std/experimental/math/traits.hpp>

namespace math = std::experimental::math;

TEST_CASE("traits: test01: is_numeric_field", "[traits]")
{
  static_assert(math::is_numeric_field_v<double>);
  static_assert(math::is_numeric_field_v<float>);
  static_assert(not math::is_numeric_field_v<int>);
}
