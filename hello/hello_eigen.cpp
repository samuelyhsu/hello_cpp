#include "Eigen/Dense"
#include "fmt/ostream.h"
#include "spdlog/spdlog.h"
#include <iostream>

using namespace Eigen;

int main(int argc, char *argv[]) {
  MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
  spdlog::info("{}", fmt::streamed(m));
  return 0;
}
