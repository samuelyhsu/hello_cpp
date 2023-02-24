#include "spdlog/spdlog.h"
#include <array>
#include <random>

int main(int argc, char *argv[]) {
  std::random_device r;
  std::mt19937 e(r());
  std::uniform_real_distribution<double> uniform_dist(0, 100);
  std::array<double, 10> datas;
  for (auto &data : datas) {
    data = uniform_dist(e);
  }
  spdlog::info("datas: {}", fmt::join(datas, ","));
  return 0;
}
