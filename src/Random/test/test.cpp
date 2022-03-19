#include <catch2/catch_test_macros.hpp>
#include "Random/Random.h"

TEST_CASE("NewRandomIsValid"){
    m1::Random random;
    REQUIRE_FALSE(&random == nullptr);
}

TEST_CASE("RandomNumberReturnsANumber"){
    m1::Random random;
    REQUIRE(random.RandomNumber(0, 1) >= 0);
}

TEST_CASE("RandomNumberGeneratesNumberInRange"){
    m1::Random random;
    uint32_t randomNum = random.RandomNumber(110, 125);
    REQUIRE(randomNum >= 110);
    REQUIRE(randomNum <= 125);
}