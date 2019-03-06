#define CATCH_CONFIG_FAST_COMPILE
#include <cassert>
#include <catch2/catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <lac/execution_policy.hpp>
#include <lac/static_vector.hpp>
#include <limits>

using vec3 = lac::static_vector<lac::cpu_execution_policy, double, 3>;
constexpr auto tolerance = std::numeric_limits<double>::epsilon();

TEST_CASE("static_vector_storage_cpu : type_check",
          "[static_vector_storage_cpu]")
{
  static_assert(lac::is_vector_storage_v<vec3>);
}

TEST_CASE("static_vector_storage_cpu : construction",
          "[static_vector_storage_cpu]")
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

TEST_CASE("static_vector_storage_cpu : iterator based access",
          "[static_vector_storage_cpu]")
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
