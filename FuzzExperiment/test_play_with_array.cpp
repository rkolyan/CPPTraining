#include "play_with_array_test_functions.h"
#include <random>
#include <iostream>
#define ITER_COUNT 1000
#define ELEM_COUNT 50

void print_vector(const std::vector<long int> &array) {
    for (const auto &elem : array) {
        std::cout << ' ' << elem;
    }
    std::cout << std::endl;
}

int main(void) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-1000000000, 1000000000);
    std::vector<long int> array;
    std::size_t cnt = 0;
    for (unsigned int size = 1; size <= ELEM_COUNT; size++) {
        for (unsigned int i = 0; i < ITER_COUNT; i++) {
            array.clear();
            array.resize(size);
            for (auto &elem : array) {
                elem = dist(mt);
            }
            auto result1 = play_with_array_my(array);
            auto result2 = play_with_array_right(array);
            if (result1 != result2) {
                std::cout << result1 << ' ' << result2 << std::endl;
                print_vector(array);
                cnt++;
            }
        }
    }
    std::cout << cnt;
    return 0;
}