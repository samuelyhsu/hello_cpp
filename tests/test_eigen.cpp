#include "Eigen/Dense"
#include "catch.hpp"
#include "fmt/ostream.h"
#include "spdlog/spdlog.h"
#include <iostream>

using namespace Eigen;

TEST_CASE("test ostream", "[eigen]") {
  MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
  spdlog::info("\n{}", fmt::streamed(m));
}

TEST_CASE("test vector", "[eigen]") {
  VectorXd v(3);
  v[0] = 3;
  v(1, 0) = 2.5;
  v(2) = -1;
  spdlog::info("rows {}, cols {}, \n{}", v.rows(), v.cols(), fmt::streamed(v));
}

TEST_CASE("Predefined Matrices", "[eigen]") {
  Matrix3d m;
  m.setIdentity();
  spdlog::info("rows {}, cols {}, \n{}", m.rows(), m.cols(), fmt::streamed(m));
}

TEST_CASE("matrix init", "[eigen]") {
  Vector3d v({1, 2, 3});
  spdlog::info("rows {}, cols {}, \n{}", v.rows(), v.cols(), fmt::streamed(v));
  v << 4, 5, 6;
  spdlog::info("rows {}, cols {}, \n{}", v.rows(), v.cols(), fmt::streamed(v));
}

TEST_CASE("basic calculations", "[eigen]") {
  Vector3d v({1, 2, 3});
  spdlog::info("v\n{}", fmt::streamed(v));
  MatrixXd m(3, 2);
  m << 4, 7, //
      5, 8,  //
      6, 9;
  spdlog::info("m\n{}", fmt::streamed(m));
  // FIXME 这里因为矩阵维度不合会导致断言失败，但是catch2还无法捕获这种问题
  MatrixXd res = v - m;
  spdlog::info("v-m\n{}", fmt::streamed(res));
}

TEST_CASE("Solving linear least squares systems", "[eigen]") {
  Matrix3f A;
  A << 1, 2, 3, //
      4, 5, 6,  //
      7, 8, 10;
  Vector3f X;
  X << -1, 1, 1;

  Vector3f b = A * X;

  spdlog::info("b = A * X\n{}", fmt::streamed(b));

#if 0
  Vector3f ls =
      A.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(b);
#else
  Vector3f ls = A.colPivHouseholderQr().solve(b);
#endif
  spdlog::info("X = b / A\n{}", fmt::streamed(ls));
}

TEST_CASE("Coefficient-wise & Array operators", "[eigen]") {
  Matrix2f A;
  A << -1, 2, //
      3, -4;

  auto abs_sum = A.array().abs().sum();
  spdlog::info("abs_sum = {}", abs_sum);
  REQUIRE(std::abs(abs_sum - 10) < 1e-6);
  REQUIRE(abs_sum != 10 + 1e-6);
}
