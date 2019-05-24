#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <std/experimental/math/serial_cpu.hpp>
#include <std/experimental/math/traits.hpp>
#include <std/experimental/math/vector.hpp>

namespace math = std::experimental::math;

TEST_CASE("traits: test01: ", "[traits]")
{
  using engine_type = math::serial_cpu_engine;
  using vector_type = math::vector<engine_type>;
  using new_vector_type
    = decltype(std::declval<vector_type>().change_engine<bool>());

  static_assert(math::uses_engine_v<vector_type, engine_type>);
  static_assert(not math::uses_engine_v<vector_type, bool>);
  static_assert(math::uses_engine_v<new_vector_type, bool>);
}
