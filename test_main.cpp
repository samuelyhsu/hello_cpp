#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "spdlog/spdlog.h"
#include "test.pb.h"
#include <Eigen/Dense>
#include <asio.hpp>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace Eigen;
using json = nlohmann::json;
using namespace std;

int f_proto(double i)
{
  MsgPerson person;
  person.set_id(i);
  std::cout << person.id() << std::endl;
  return person.id();
}

int f_eigen()
{
  MatrixXd test = MatrixXd::Zero(1, 1);
  std::cout << test << std::endl;
  return 0;
}

int f_fmt(double i)
{
  fmt::print("fmt-testing\n");
  return i + 1;
}

int f_json()
{
  json j = "{ \"nlohmann-json\": true, \"pi\": 3.141 }"_json;
  std::cout << j.dump(4) << std::endl;
  return 2;
}

TEST_CASE("vectors can be sized and resized", "[vector]")
{
  REQUIRE(f_proto(2) == 2);
  REQUIRE(f_proto(1) == 1);
  REQUIRE(f_proto(3) == 3);
  REQUIRE(f_fmt(1) == 2);
  REQUIRE(f_fmt(0) == 1);
  REQUIRE(f_fmt(0) == 1);
  REQUIRE(f_json() == 2);
  REQUIRE(f_proto(4) == 4);
  REQUIRE(f_eigen() == 0);
}
