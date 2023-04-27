#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "my_epidemic.hpp"
#include <vector>

TEST_CASE("Testing struct PandemicData") {
    PandemicData test_pd = {1000, 10, 5, 3, 2, 100, 50, 200, 0, 0, 0.5, 0.8, 0.5, 0.1};

    CHECK(test_pd.Susc == 1000);
    CHECK(test_pd.Inf == 10);
    CHECK(test_pd.Dead == 5);
    CHECK(test_pd.Heal == 3);
    CHECK(test_pd.Rec == 2);
    CHECK(test_pd.Imm == 100);
    CHECK(test_pd.PanStart == 50);
    CHECK(test_pd.VaxStart == 200);
    CHECK(test_pd.VaxMax == 0);
    CHECK(test_pd.NewSusc == 0);
    CHECK(test_pd.Beta == 0.5);
    CHECK(test_pd.Gamma == 0.8);
    CHECK(test_pd.HealIndex == 0.5);
    CHECK(test_pd.VaxIndex == 0.1);
}

TEST_CASE("Contagion generate_data returns the expected results") {
    PandemicData initial_state{1000, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0.3};
    Contagion test_cont{initial_state,'n'};
    int duration{10};
    std::vector<PandemicData> expected_data{
        {1000, 10, 0,   0,   0, 1, 0, 1, 1,   0, 0.3, 0.05, 0.5, 0.3},
        {997,  12, 0,   1,   1, 1, 0, 1, 1,   0, 0.3, 0.05, 0.5, 0.3},
        {696,  15, 0, 299, 299, 1, 0, 1, 1,   0, 0.3, 0.05, 0.5, 0.3},
        {485,  17, 0, 508, 508, 1, 0, 1, 1,   1, 0.3, 0.05, 0.5, 0.3},
        {547,  18, 0, 445, 445, 1, 0, 1, 1, 298, 0.3, 0.05, 0.5, 0.3},
        {527,  20, 0, 463, 463, 1, 0, 1, 1, 210, 0.3, 0.05, 0.5, 0.3},
        {531,  22, 0, 457, 457, 1, 0, 1, 1, 235, 0.3, 0.05, 0.5, 0.3},
        {529,  24, 0, 457, 457, 1, 0, 1, 1, 228, 0.3, 0.05, 0.5, 0.3},
        {527,  27, 0, 456, 456, 1, 0, 1, 1, 229, 0.3, 0.05, 0.5, 0.3},
        {525,  30, 0, 455, 455, 1, 0, 1, 1, 228, 0.3, 0.05, 0.5, 0.3},
        {523,  33, 1, 453, 454, 1, 0, 1, 1, 228, 0.3, 0.05, 0.5, 0.3}
    };

    auto result = test_cont.generate_data(duration);
    CHECK(operator==(result,expected_data));
}
