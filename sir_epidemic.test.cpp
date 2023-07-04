#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
#include "sir_epidemic.hpp"
#include "sir_operator.hpp"
#include "date.hpp"

TEST_CASE("Testing struct SirData") {
  epidemic::SirData test_pd = {1000, 10, 2};

  CHECK(test_pd.Susc == 1000);
  CHECK(test_pd.Inf == 10);
  CHECK(test_pd.Rec == 2);
}

TEST_CASE("Contagion generate_data returns the expected results") {
  epidemic::SirData initial_state{1000, 10, 8};
  epidemic::Simulation test_cont{initial_state, 0.3, 0.5};
  int duration{10};
  std::vector<epidemic::SirData> expected_data{
      {1000, 10, 8}, {997, 8, 13}, {995, 6, 17}, {993, 5, 20},
      {992, 3, 23},  {991, 2, 25}, {990, 2, 26}, {989, 2, 27},
      {988, 2, 28},  {987, 2, 29}, {986, 2, 30}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}

TEST_CASE("Beta e Gamma test") {
  epidemic::SirData initial_state{10, 10, 0};
  epidemic::Simulation test_cont{initial_state, 1, 0};
  int duration_1{1};
  std::vector<epidemic::SirData> expected_data{
      {10, 10, 0},
      {5, 15, 0},
  };
  auto result = test_cont.generate_data(duration_1);
  CHECK(operator==(result, expected_data));
}

TEST_CASE("Test di FinalDate in date.hpp") {
  auto test_day = FinalDate(0);
  std::chrono::system_clock::time_point day_0 =
      std::chrono::system_clock::now();
  auto test_day_time =
      std::chrono::time_point_cast<std::chrono::seconds>(test_day);
  auto day_0_time = std::chrono::time_point_cast<std::chrono::seconds>(day_0);
  REQUIRE(test_day_time == day_0_time);
}

TEST_CASE("Test operatore == in sir_operator.hpp") {
  std::vector<epidemic::SirData> sirdata_1{
      {-410, 10, 0},
      {5, 315, 0},
  };
  std::vector<epidemic::SirData> sirdata_2{
      {-410, 10, 0},
      {5, 315, 0},
  };
}