#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
#include "sir.hpp"

TEST_CASE("Testing struct SirData") {
  SirData test_pd = {1000, 10, 2, 0.5, 0.8};

  CHECK(test_pd.Susc == 1000);
  CHECK(test_pd.Inf == 10);
  CHECK(test_pd.Rec == 2);
  CHECK(test_pd.Beta == 0.5);
  CHECK(test_pd.Gamma == 0.8);
}

TEST_CASE("Contagion generate_data returns the expected results") {
  SirData initial_state{1000, 10, 8, 0.3, 0.05};
  Simulation test_cont{initial_state};
  int duration{10};
  std::vector<SirData> expected_data{
      {1000, 10, 8, 0.3, 0.05,},
      {997, 12, 9, 0.3, 0.05},
      {993, 15, 10, 0.3, 0.05},
      {989, 18, 11, 0.3, 0.05},
      {984, 22, 12, 0.3, 0.05},
      {978, 27, 13, 0.3, 0.05},
      {970, 34, 14, 0.3, 0.05},
      {960, 42, 16, 0.3, 0.05},
      {948, 52, 18, 0.3, 0.05},
      {933, 64, 21, 0.3, 0.05},
      {915, 79, 24, 0.3, 0.05}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}