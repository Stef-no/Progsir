#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
#include "my_epidemic.hpp"

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
  PandemicData initial_state{1000, 10, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0.3};
  Contagion test_cont{initial_state, 'y', 180, 1, 'n', 1, 'n', 1, 0, 1, 1, 'n'};
  int duration{10};
  std::vector<PandemicData> expected_data{
      {1000, 10, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0.3},
      {997, 12, 1, 0, 1, 0, 0.3, 0.05, 0.5, 0.3},
      {696, 15, 2, 297, 299, 0, 0.3, 0.05, 0.5, 0.3},
      {485, 17, 3, 505, 508, 0, 0.3, 0.05, 0.5, 0.3},
      {546, 18, 4, 442, 446, 297, 0.3, 0.05, 0.5, 0.3},
      {525, 20, 5, 460, 465, 208, 0.3, 0.05, 0.5, 0.3},
      {529, 22, 6, 453, 459, 234, 0.3, 0.05, 0.5, 0.3},
      {526, 24, 7, 453, 460, 226, 0.3, 0.05, 0.5, 0.3},
      {524, 27, 8, 451, 459, 227, 0.3, 0.05, 0.5, 0.3},
      {521, 30, 9, 450, 459, 226, 0.3, 0.05, 0.5, 0.3},
      {518, 33, 10, 449, 459, 225, 0.3, 0.05, 0.5, 0.3}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}
