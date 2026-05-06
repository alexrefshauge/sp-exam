#include <doctest/doctest.h>
#include <Reaction.hpp>

TEST_SUITE("reaction syntax tests")
{
    TEST_CASE("make reaction")
    {
        auto p = (stochastic::ReactionSide{0} >> 2.0);
        static_assert(std::is_same<decltype(p), stochastic::ReactionProducer>::value);
        auto r = p >>= stochastic::ReactionSide{1};
        static_assert(std::is_same<decltype(r), stochastic::Reaction>::value);

        CHECK_EQ(r.consume_id, 0);
        CHECK_EQ(r.produce_id, 1);
    }
}