#include <vector>
#include <iostream>

int main(void) {
    std::vector<int> vec = {1, 2, 3, 2, 4};
    auto iter = vec.cbegin();
    do {
        ++iter;
        std::cout << std::distance(iter, vec.cend()) << std::endl;
    } while (iter != vec.cend());
    std::cout << std::distance(std::prev(vec.cbegin()), vec.cend()) << std::endl;
    std::cout << std::distance(std::prev(vec.cbegin(), 2), vec.cend()) << std::endl;
    std::cout << std::distance(std::next(vec.cend()), vec.cend()) << std::endl;
    return 0;
}