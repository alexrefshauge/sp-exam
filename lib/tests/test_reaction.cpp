#include <vector>
#include <utility>
#include <doctest/doctest.h>
#include <Reaction.hpp>

TEST_SUITE("reaction syntax tests")
{
    TEST_CASE("reaction with 2 inputs")
    {
        stochastic::Species A("A", 1);
        stochastic::Species B("B", 1);
        stochastic::Species C("C", 1);
        auto rate = 0.5;

        auto reaction = A + B >> rate >>= C;
        CHECK_EQ(reaction.inputs[0], "A");
        CHECK_EQ(reaction.inputs[1], "B");
        CHECK_EQ(reaction.product[0], "C");
        CHECK_EQ(reaction.rate, rate);
    }

    TEST_CASE("reaction with 2 outputs")
    {
        stochastic::Species A("A", 1);
        stochastic::Species B("B", 1);
        stochastic::Species C("C", 1);
        auto rate = 0.2;

        auto reaction = A >> rate >>= B + C;
        CHECK_EQ(reaction.inputs[0], "A");
        CHECK_EQ(reaction.product[0], "B");
        CHECK_EQ(reaction.product[1], "C");
        CHECK_EQ(reaction.rate, rate);
    }
}
