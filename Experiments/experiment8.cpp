#include <vector>
#include <numeric>
#include <iostream>

int main(void) {
    std::vector<unsigned int> vec = {1, 2, 3, 3, 1, 4};
    auto result = std::accumulate(vec.cbegin(), vec.cend(), 0);
    std::cout << result;
    return 0;
}