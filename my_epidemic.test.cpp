#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include <vector>

#include "date.hpp"
#include "doctest.h"
#include "my_epidemic.hpp"
#include "my_operator.hpp"

TEST_CASE("Testing struct PandemicData") {
  epidemic::PandemicPop test_pop{1000, 10, 5, 3, 2, 0};
  epidemic::PandemicIndex test_index{0.5, 0.8, 0.5};
  epidemic::PandemicData test_pd = {test_pop, test_index};

  CHECK(test_pd.EpidemicPop.Susc == 1000);
  CHECK(test_pd.EpidemicPop.Inf == 10);
  CHECK(test_pd.EpidemicPop.Dead == 5);
  CHECK(test_pd.EpidemicPop.Heal == 3);
  CHECK(test_pd.EpidemicPop.Rec == 2);
  CHECK(test_pd.EpidemicPop.NewSusc == 0);
  CHECK(test_pd.EpidemicIndex.Beta == 0.5);
  CHECK(test_pd.EpidemicIndex.Gamma == 0.8);
  CHECK(test_pd.EpidemicIndex.DeadIndex == 0.5);
}

TEST_CASE("Contagion generate_data returns the expected results") {
  epidemic::PandemicPop initial_pop{990, 10, 0, 0, 0, 0};
  epidemic::PandemicIndex initial_index{0.3, 0.05, 0.5};
  epidemic::PandemicData initial_state{initial_pop, initial_index};
  epidemic::VarIndex test_di{'n', 0, 0};
  epidemic::VarIndex test_beta{'n', 0, 0};
  epidemic::VarIndex test_gamma{'n', 0, 0};
  epidemic::VarIndex test_vax{'n', 0, 0};
  epidemic::Contagion test_cont{initial_state, test_di, test_beta, test_gamma,
                                test_vax,      0.0,     1,         0};
  int duration{10};
  std::vector<epidemic::PandemicData> expected_data{
      {990, 10, 0, 0, 0, 0, 0.3, 0.05, 0.5},
      {987, 12, 1, 0, 1, 0, 0.3, 0.05, 0.5},
      {983, 15, 2, 0, 2, 0, 0.3, 0.05, 0.5},
      {979, 18, 3, 0, 3, 0, 0.3, 0.05, 0.5},
      {974, 22, 4, 0, 4, 0, 0.3, 0.05, 0.5},
      {968, 27, 5, 0, 5, 0, 0.3, 0.05, 0.5},
      {960, 34, 6, 0, 6, 0, 0.3, 0.05, 0.5},
      {950, 42, 7, 1, 8, 0, 0.3, 0.05, 0.5},
      {938, 52, 8, 2, 10, 0, 0.3, 0.05, 0.5},
      {924, 64, 10, 2, 12, 1, 0.3, 0.05, 0.5},
      {907, 79, 12, 2, 14, 1, 0.3, 0.05, 0.5}};

  auto result = test_cont.generate_data(duration);
  CHECK(operator==(result, expected_data));
}

TEST_CASE("Beta e Gamma test") {
  epidemic::PandemicPop initial_pop{10, 10, 0, 0, 0, 0};
  epidemic::PandemicIndex initial_index{1.0, 0.0, 0.0};
  epidemic::PandemicData initial_state{initial_pop, initial_index};
  epidemic::VarIndex test_di{'n', 0, 0};
  epidemic::VarIndex test_beta{'n', 0, 0};
  epidemic::VarIndex test_gamma{'n', 0, 0};
  epidemic::VarIndex test_vax{'n', 0, 0};
  epidemic::Contagion test_cont{initial_state, test_di, test_beta, test_gamma,
                                test_vax, 0.0,     1,       0};
  int duration_1{1};
  std::vector<epidemic::PandemicData> expected_data{
      {10, 10, 0, 0, 0, 0, 1.0, 0.0, 0.0},
      {5, 15, 0, 0, 0, 0, 1.0, 0.0, 0.0},
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

TEST_CASE("Test operatore == in my_operator.hpp") {
  std::vector<epidemic::PandemicData> data_1{
      {-410, 10, 0, 0, 0, 0, 5.6, 0.0, 12.0},
      {5, 315, 0, 30, 0, 0, 1.0, 10.06, 0.0},
  };
  std::vector<epidemic::PandemicData> data_2{
      {-410, 10, 0, 0, 0, 0, 5.6, 0.0, 12.0},
      {5, 315, 0, 30, 0, 0, 1.0, 10.06, 0.0},
  };
}
