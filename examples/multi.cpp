#include "models.cpp"

int main()
{
    auto v = abc(100, 0, 1);
    SimPool p{};
    v.simulate_multi(10, 42, 100);
}