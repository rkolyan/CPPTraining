#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::vector<unsigned int> vec = {1, 5, 2, 3, 16, 7};
    std::sort(vec.begin(), vec.end(), [](unsigned int a, unsigned int b){return b < a;});
    for (const auto &element : vec) {
        std::cout << element << ' ';
    }
    return 0;
}