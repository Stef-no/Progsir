#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "my_epidemic.hpp"
#include <vector>

TEST_CASE("Testing struct PandemicData") {
    PandemicData test_pd = {1000, 10, 5, 3, 2, 100, 50, 200, 0, 0, 0.5, 0.8, 0.5, 0, 'y'};

    CHECK(test_pd.Susc_ == 1000);
    CHECK(test_pd.Inf_ == 10);
    CHECK(test_pd.Dead_ == 5);
    CHECK(test_pd.Heal_ == 3);
    CHECK(test_pd.Rec_ == 2);
    CHECK(test_pd.Imm_ == 100);
    CHECK(test_pd.PanStart_ == 50);
    CHECK(test_pd.VaxStart_ == 200);
    CHECK(test_pd.VaxMax_ == 0);
    CHECK(test_pd.NewSusc_ == 0);
    CHECK(test_pd.Beta_ == 0.5);
    CHECK(test_pd.Gamma_ == 0.8);
    CHECK(test_pd.HealIndex_ == 0.5);
    CHECK(test_pd.VaxIndex_ == 0.0);
    CHECK(test_pd.Previous_ == 'y');
}

TEST_CASE("Contagion generate_data returns the expected results") {
    PandemicData initial_state{1000, 10, 2, 0, 2, 0, 0, 0, 0, 0, 0.3, 0.05, 0.5, 0.3, 'y'};
    Contagion test_cont{initial_state};
    int duration{10};
    std::vector<PandemicData> expected_data{
        {1000, 10, 2,   0,   2, 0, 0, 0, 0,   0, 0.3, 0.05, 0.5, 0.3, 'y'},
        {697,  12, 2, 301, 303, 0, 0, 0, 0,   0, 0.3, 0.05, 0.5, 0.3, 'y'},
        {697,  13, 2, 300, 302, 0, 0, 0, 0, 301, 0.3, 0.05, 0.5, 0.3, 'y'},
        {695,  15, 2, 300, 302, 0, 0, 0, 0, 300, 0.3, 0.05, 0.5, 0.3, 'y'},
        {694,  17, 2, 299, 301, 0, 0, 0, 0, 300, 0.3, 0.05, 0.5, 0.3, 'y'},
        {693,  19, 2, 298, 300, 0, 0, 0, 0, 299, 0.3, 0.05, 0.5, 0.3, 'y'},
        {690,  22, 2, 298, 300, 0, 0, 0, 0, 298, 0.3, 0.05, 0.5, 0.3, 'y'},
        {687,  26, 2, 297, 299, 0, 0, 0, 0, 298, 0.3, 0.05, 0.5, 0.3, 'y'},
        {684,  30, 2, 296, 298, 0, 0, 0, 0, 297, 0.3, 0.05, 0.5, 0.3, 'y'},
        {680,  34, 3, 295, 298, 0, 0, 0, 0, 296, 0.3, 0.05, 0.5, 0.3, 'y'},
        {676,  39, 4, 293, 297, 0, 0, 0, 0, 295, 0.3, 0.05, 0.5, 0.3, 'y'}
    };

    auto result = test_cont.generate_data(duration);
    CHECK(result == expected_data);
}
