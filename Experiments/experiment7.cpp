#include <set>
#include <iostream>

int main(void) {
    std::multiset<unsigned int> set = {1, 2, 3, 3, 2, 4};
    for (const auto &element : set) {
        std::cout << element << ' ';
    }
    return 0;
}