#define CATCH_CONFIG_FAST_COMPILE
#include <cassert>
#include <catch2/catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <testlac/meta/testpath.hpp>
#include <testlac/tools/wsv.hpp>
#include <vector>

auto generate_validinput01()
  -> testlac::tools::wsv_data<std::size_t, std::allocator<void>>;

namespace fs = std::experimental::filesystem;

TEST_CASE("fileio : wsv: read validinput01.wsv", "[fileio][wsv]")
{
  constexpr auto testpath = testlac::meta::test_path();
  constexpr auto testdatadir = testpath.data;
  std::string wsvdatadir = std::string(testdatadir) + std::string("/tools/wsv");

  auto const validinput01 = wsvdatadir + "/validinput01.wsv";
  if (not std::experimental::filesystem::exists(validinput01)) {
    throw std::runtime_error("testdata file not found");
  }
  auto const wsvdata = testlac::tools::read_wsv<std::size_t>(validinput01);

  auto const exact_wsvdata = generate_validinput01();
  REQUIRE(wsvdata.data == exact_wsvdata.data);
}

TEST_CASE("fileio : wsv: write validinput01.wsv", "[fileio][wsv]")
{
  constexpr auto testpath = testlac::meta::test_path();
  constexpr auto testoutputdir = testpath.output;
  std::string wsvoutputdir
    = std::string(testoutputdir) + std::string("/tools/wsv");
  fs::create_directories(wsvoutputdir);

  auto const exact_wsvdata = generate_validinput01();

  auto const validoutput01 = wsvoutputdir + "/validoutput01.wsv";
  testlac::tools::write(validoutput01, exact_wsvdata);

  auto const wsvdata = testlac::tools::read_wsv<std::size_t>(validoutput01);
  REQUIRE(wsvdata.data == exact_wsvdata.data);
}

auto generate_validinput01()
  -> testlac::tools::wsv_data<std::size_t, std::allocator<void>>
{
  auto wsv = testlac::tools::wsv_data<std::size_t, std::allocator<void>>();
  auto& data = wsv.data;
  std::size_t ndata = 3;
  std::size_t npoint = 7;
  data.resize(ndata);
  for (auto& col : data) {
    col.resize(npoint);
  }

  for (std::size_t i = 0; i < npoint; ++i) {
    for (std::size_t j = 0; j < ndata; ++j) {
      data[j][i] = 10 * i + j + 1;
    }
  }

  return wsv;
}
