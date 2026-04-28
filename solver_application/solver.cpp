#include <iostream>
#include <string>
#include "../formatter_ex_lib/formatter_ex.h"
#include "../solver_lib/solver.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: solver <a> <b> <c> <eps> [x1] [x2]" << std::endl;
        return 1;
    }

    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);
    double eps = (argc >= 5) ? std::stod(argv[4]) : 1e-6;
    double x1 = (argc >= 6) ? std::stod(argv[5]) : -1000;
    double x2 = (argc >= 7) ? std::stod(argv[6]) : 1000;

    std::cout << "Searching root on interval [" << x1 << ", " << x2 << "]" << std::endl;

    Solver solver;
    double root = solver.findRoot(a, b, c, eps, x1, x2);

    std::cout << formatter_ex("Root: " + std::to_string(root));

    return 0;
}
