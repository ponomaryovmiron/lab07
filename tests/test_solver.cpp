#include <solver.hpp>

#include <gtest/gtest.h>

TEST(Solver, QuadraticEquation)
{
    double x1 = 0;
    double x2 = 0;

    solve(1, 2, 1, x1, x2);

    EXPECT_DOUBLE_EQ(x1, -1);
    EXPECT_DOUBLE_EQ(x2, -1);
}
