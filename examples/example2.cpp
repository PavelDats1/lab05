#include "../include/print.hpp"
#include <fstream>

int main() {
    std::ofstream log("../log.txt");
    print("hello", log);
    return 0;
}
