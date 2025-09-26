#include <set>
#include <vector>
#include <iostream>

int main(void) {
    std::multiset<unsigned int> values = {1, 2, 3, 2, 3, 3, 11};
    std::vector<unsigned int> values2(values.cbegin(), values.cend());

    for (const auto &element : values2) {
        std::cout << element << ' ';
    }
    return 0;
}