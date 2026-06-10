#include <formatter_ex.hpp>
#include <solver.hpp>

#include <iostream>
#include <string>

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;

    std::cin >> a >> b >> c;

    double x1 = 0;
    double x2 = 0;

    solve(a, b, c, x1, x2);

    std::cout << format_ex("x1 = " + std::to_string(x1)) << std::endl;
    std::cout << format_ex("x2 = " + std::to_string(x2)) << std::endl;

    return 0;
}
