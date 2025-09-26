//
// Created by rkolyan on 27.01.2025.
//

#include <iostream>
#include <set>
#include <list>

typedef unsigned int xor_t;

int main(void) {
    std::set<xor_t> xors;
    unsigned int q = 0, tmp = 0;
    std::cin >> q;
    std::list<unsigned int> nums;
    for (unsigned int i = 0; i < q; i++) {
        std::cin >> tmp;
        nums.push_front(tmp);
        for (const auto &element : nums) {
            xors.insert(element ^ tmp);
        }
        std::cout << *(xors.crbegin()) << std::endl;
    }
    return 0;
}