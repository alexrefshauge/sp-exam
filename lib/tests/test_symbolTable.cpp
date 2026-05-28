#include <doctest/doctest.h>
#include <SymbolTable.hpp>
#include <string>

TEST_SUITE("Symbol table tests")
{

    TEST_CASE("store")
    {
        stochastic::SymbolTable<std::string, size_t> table{};
        size_t v = 42;
        table.store("A", v);
        CHECK_EQ(table.size(), 1);
    }

    TEST_CASE("get")
    {
        stochastic::SymbolTable<std::string, size_t> table{};
        size_t v = 42;
        table.store("A", v);

        CHECK_EQ(table.lookup("A"), 42);
    }

    TEST_CASE("store duplicate failure")
    {
        stochastic::SymbolTable<std::string, size_t> table{};
        size_t x = 1;
        size_t y = 2;
        table.store("A", x);
        CHECK_THROWS(table.store("A", y));
        CHECK_MESSAGE(table.lookup("A") == 1, "A should still hold original value");
    }

    TEST_CASE("get not found failure")
    {
        stochastic::SymbolTable<std::string, size_t> table{};
        size_t x = 1;
        size_t y = 2;
        table.store("A", x);
        CHECK_THROWS(table.lookup("B"));
    }
}