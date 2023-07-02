#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
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

TEST_CASE("Crazy test") {
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