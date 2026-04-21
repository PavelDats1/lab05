#include <iostream>
#include "sum.h"
int main() {
    int a = 10;
    int b = 20;
    int result = sum(a, b);
    std::cout << "Сумма " << a << " + " << b << " = " << result << std::endl;
    return 0;
}
