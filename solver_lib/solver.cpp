#include "solver.hpp"

#include <cmath>

void solve(double a, double b, double c, double& x1, double& x2)
{
    double d = b * b - 4 * a * c;

    x1 = (-b + std::sqrt(d)) / (2 * a);
    x2 = (-b - std::sqrt(d)) / (2 * a);
}
