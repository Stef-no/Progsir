#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include <vector>

#include "doctest.h"
#include "my_date.hpp"
#include "my_epidemic.hpp"
#include "my_operator.hpp"

TEST_CASE("Testing struct PandemicData") {
  PandemicData test_pd = {1000, 10, 5, 3, 2, 0, 0.5, 0.8, 0.5, 0.1};

  CHECK(test_pd.Susc == 1000);
  CHECK(test_pd.Inf == 10);
  CHECK(test_pd.Dead == 5);
  CHECK(test_pd.Heal == 3);
  CHECK(test_pd.Rec == 2);
  CHECK(test_pd.NewSusc == 0);
  CHECK(test_pd.Beta == 0.5);
  CHECK(test_pd.Gamma == 0.8);
  CHECK(test_pd.DeadIndex == 0.5);
  CHECK(test_pd.VaxIndex == 0.1);
}

TEST_CASE("Contagion generate_data returns the expected results") {
  PandemicData initial_state{990, 10, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0};
  VarIndex test_di{'n', 0, 0};
  VarIndex test_beta{'n', 0, 0};
  VarIndex test_gamma{'n', 0, 0};
  VarIndex test_vax{'n', 0, 0};
  Contagion test_cont{initial_state, test_di, test_beta, test_gamma,
                      test_vax,      1,       0};
  int duration{10};
  std::vector<PandemicData> expected_data{
      {990, 10, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0},
      {987, 12, 1, 0, 1, 0, 0.3, 0.05, 0.5, 0},
      {983, 15, 2, 0, 2, 0, 0.3, 0.05, 0.5, 0},
      {979, 18, 3, 0, 3, 0, 0.3, 0.05, 0.5, 0},
      {974, 22, 4, 0, 4, 0, 0.3, 0.05, 0.5, 0},
      {968, 27, 5, 0, 5, 0, 0.3, 0.05, 0.5, 0},
      {960, 34, 6, 0, 6, 0, 0.3, 0.05, 0.5, 0},
      {950, 42, 7, 1, 8, 0, 0.3, 0.05, 0.5, 0},
      {938, 52, 8, 2, 10, 0, 0.3, 0.05, 0.5, 0},
      {924, 64, 10, 2, 12, 1, 0.3, 0.05, 0.5, 0},
      {907, 79, 12, 2, 14, 1, 0.3, 0.05, 0.5, 0}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}

TEST_CASE("Beta test") {
  PandemicData initial_state{10, 10, 0, 0, 0, 0, 1.0, 0.0, 0.0, 0.0};
  VarIndex test_di{'n', 0, 0};
  VarIndex test_beta{'n', 0, 0};
  VarIndex test_gamma{'n', 0, 0};
  VarIndex test_vax{'n', 0, 0};
  Contagion test_cont{initial_state, test_di, test_beta, test_gamma,
                      test_vax,      1,       0};
  int duration_1{1};
  std::vector<PandemicData> expected_data{
      {10, 10, 0, 0, 0, 0, 1.0, 0.0, 0.0, 0.0},
      {5, 15, 0, 0, 0, 0, 1.0, 0.0, 0.0, 0.0},
  };
  auto result = test_cont.generate_data(duration_1);
  CHECK(operator==(result, expected_data));
}

TEST_CASE("Test di FinalDate in my_date.hpp") {
  auto test_day = FinalDate(0);
  std::chrono::system_clock::time_point day_0 =
      std::chrono::system_clock::now();
  auto test_day_time = std::chrono::time_point_cast<std::chrono::seconds>(test_day);
  auto day_0_time = std::chrono::time_point_cast<std::chrono::seconds>(day_0);
  REQUIRE(test_day_time == day_0_time);
}

TEST_CASE("Test operatore == in my_operator.hpp") {
  std::vector<PandemicData> data_1{
      {-410, 10, 0, 0, 0, 0, 5.6, 0.0, 12.0, 0.0},
      {5, 315, 0, 30, 0, 0, 1.0, 10.06, 0.0, 210.0},
  };
  std::vector<PandemicData> data_2{
      {-410, 10, 0, 0, 0, 0, 5.6, 0.0, 12.0, 0.0},
      {5, 315, 0, 30, 0, 0, 1.0, 10.06, 0.0, 210.0},
  };
}

