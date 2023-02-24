#include "catch.hpp"

TEST_CASE("test REQUIRE", "[catch2]") {
  REQUIRE(true);
  REQUIRE(1 == 1);
  REQUIRE(1 == 1.0);
  double a = 1;
  REQUIRE(a != 1.1f);
}
