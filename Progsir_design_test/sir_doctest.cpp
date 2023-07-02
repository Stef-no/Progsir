#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>

#include "doctest.h"
#include "sir.hpp"
#include "sir.cpp"
#include "sir_operator.hpp"

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
      {1000, 10,  8},
      {997,   8, 13},
      {995,   6, 17},
      {993,   5, 20},
      {992,   3, 23},
      {991,   2, 25},
      {990,   2, 26},
      {989,   2, 27},
      {988,   2, 28},
      {987,   2, 29},
      {986,   2, 30}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}