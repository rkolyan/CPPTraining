#include <random>
#include <iostream>
#include "list_stack_proverka.h"
#define ITER_COUNT 100
#define ELEM_COUNT 10

void print_list_nodes(const std::list<Node> nodes) {
    for (const auto &elem : nodes) {
        std::cout << '(' << elem.width << ',' << elem.height << ") ";
    }
    std::cout << std::endl;
}

int main(void) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(1, 100);
    std::list<Node> list;
    std::size_t cnt = 0;
    for (unsigned int i = 0; i < ITER_COUNT; i++) {
        list.clear();
        for (unsigned int j = 0; j < ELEM_COUNT; j++) {
            list.emplace_back(dist(mt), dist(mt));       
        }
        auto result1 = is_fully_intersected(list);
        auto result2 = is_fully_intersected_right(list);
        if (result1 != result2) {
            std::cout << result1 << ' ' << result2 << std::endl;
            print_list_nodes(list);
            cnt++;
        }
    }
    std::cout << cnt;
    return 0;
}