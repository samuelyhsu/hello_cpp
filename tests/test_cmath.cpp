#include "catch.hpp"
#include <cmath>

TEST_CASE("test pow", "[eigen]") {
  BENCHMARK("std::pow 2", i) {
    return std::pow(i, 2);
  }; // MSVC2019 amd64: Mean: 46.5094 ns
  BENCHMARK("common square", i) {
    return i * i;
  }; // MSVC2019 amd64: Mean: 5.91243 ns
  BENCHMARK("std::pow 3", i) {
    return std::pow(i, 3);
  }; // MSVC2019 amd64: Mean: 43.8817 ns
  BENCHMARK("common cube", i) {
    return i * i * i;
  }; // MSVC2019 amd64: Mean: 5.4939 ns
}
