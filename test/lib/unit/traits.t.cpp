#define CATCH_CONFIG_FAST_COMPILE
#include <cassert>
#include <catch2/catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <lac/traits.hpp>

struct arbitrary_type {
};

TEST_CASE("traits: is_float_field", "[traits]")
{
  static_assert(lac::is_float_field_v<int>);
  static_assert((not lac::is_float_field_v<arbitrary_type>));
}
