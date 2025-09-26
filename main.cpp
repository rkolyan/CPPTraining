#include <iostream>

int main() {
    int num = -2147483648;
    std::cout << std::abs(static_cast<int>(-2147483648)) << std::endl;
    std::cout << -num << std::endl;
    return 0;
}
