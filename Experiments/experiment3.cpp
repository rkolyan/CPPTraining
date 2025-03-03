//
// Created by rkolyan on 18.01.2025.
//

#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1};
    if (std::prev(vec.begin()) == vec.end())
        std::cout << "fdsfafdsf";
    return 0;
}