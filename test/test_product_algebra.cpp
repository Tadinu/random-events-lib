#include "variable.h"
#include "set.h"
#include "gtest/gtest.h"
#include "product_algebra.h"
#include "interval.h"


auto x = Continuous("x");
auto y = Continuous("y");

auto a = Symbolic("a", Set({"a", "b", "c"}));
auto u = Symbolic("u", Set({"u", "v", "w"}));

TEST(ProductAlgebra, Intersection){
    auto unit_interval = closed(0, 1);
    VariableAssignmentType vmap_1 = {{x, unit_interval}, {y, unit_interval}};
    auto event1 = SimpleEvent(vmap_1);

}