#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>

#include "PortableCollection.h"
#include "PortableHostCollection.h"
#include "SoACommon.h"
#include "SoALayout.h"
#include "SoAView.h"

namespace {
  GENERATE_SOA_LAYOUT(TestLayout, SOA_COLUMN(double, x), SOA_COLUMN(int32_t, id))

  using TestSoA = TestLayout<>;

  constexpr auto s_tag = "[PortableCollection]";
}  // namespace

// This test is currently mostly about the code compiling
TEST_CASE("Use of PortableCollection<T, TDev> on host code", s_tag) {
  auto const size = 10;

  alpaka::DevCpu const& host = alpaka::getDevByIdx(alpaka::PlatformCpu{}, 0);

  PortableCollection<TestSoA, alpaka::DevCpu> coll(size, host);

  SECTION("Tests") { REQUIRE(coll->metadata().size() == size); }

  static_assert(std::is_same_v<PortableCollection<TestSoA, alpaka::DevCpu>, PortableHostCollection<TestSoA>>);
}
