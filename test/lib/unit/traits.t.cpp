#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <std/experimental/math/traits.hpp>
#include <teststd/experimental/math/traits.hpp>

namespace math = std::experimental::math;
namespace testmath = teststd::experimental::math;

TEST_CASE("traits: test01: is_numeric_field", "[traits]")
{
  static_assert(math::is_numeric_field_v<double>);
  static_assert(math::is_numeric_field_v<float>);
  static_assert(not math::is_numeric_field_v<int>);
}

TEST_CASE("traits: test02: engine related traits", "[traits]")
{
  static_assert(math::is_engine_aware_v<testmath::traits_test02_struct_01>);
  static_assert(not math::is_engine_aware_v<testmath::traits_test02_struct_02>);

  static_assert(math::uses_engine_v<int, testmath::traits_test02_struct_01>);
  static_assert(
    not math::uses_engine_v<void, testmath::traits_test02_struct_01>);
  static_assert(
    not math::uses_engine_v<int, testmath::traits_test02_struct_02>);

  static_assert(math::uses_engine_v<int, testmath::traits_test02_struct_03a>);

  static_assert(math::uses_engine_v<int,
                                    testmath::traits_test02_struct_03a,
                                    testmath::traits_test02_struct_03b>);
}
