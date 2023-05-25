#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
#include "sir.hpp"

TEST_CASE("Testing struct SirData") {
  SirData test_pd = {1000, 10, 2};

  CHECK(test_pd.Susc == 1000);
  CHECK(test_pd.Inf == 10);
  CHECK(test_pd.Rec == 2);
}

TEST_CASE("Contagion generate_data returns the expected results") {
  SirData initial_state{1000, 10, 8};
  Simulation test_cont{initial_state, 0.3, 0.5};
  int duration{10};
  std::vector<SirData> expected_data{
      {1000, 10, 8},
      {997, 12, 9},
      {993, 15, 10},
      {989, 18, 11},
      {984, 22, 12},
      {978, 27, 13},
      {970, 34, 14},
      {960, 42, 16},
      {948, 52, 18},
      {933, 64, 21},
      {915, 79, 24}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}