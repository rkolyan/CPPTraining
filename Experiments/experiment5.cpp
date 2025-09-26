#include <set>
#include <iostream>

int main(void) {
    std::set<unsigned int, std::greater<>> myset {1, 3, 5};
    std::cout << *myset.upper_bound(2) << std::endl;
    std::cout << *myset.upper_bound(3) << std::endl;
    std::cout << *myset.upper_bound(4) << std::endl;
    std::cout << *myset.upper_bound(5) << std::endl;

    return 0;
}