//
// Created by rkolyan on 15.04.2024.
//

#include <iostream>
#include <set>

//Задача на совместном использовании структуры


struct Node {
    int index;
    int value;
    bool operator<(const Node &element) const {
        return value < element.value;
    };
    bool operator==(const Node &element) const {
        return value == element.value && index == element.index;
    };
    Node(int index, int value) {
        this->index = index;
        this->value = value;
    }
};

int main(void) {
    int N = 0, value;
    std::set<Node> nodes;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> value;
        nodes.insert(Node(i, value));
    }

    auto a_begin_iterator = nodes.begin(), a_end_iterator = std::next(a_begin_iterator, N / 2 + N % 2 - 1);
    //1) Первый граничный случай
    double diam = std::prev(nodes.end())->value - std::next(a_end_iterator)->value;
    double diam2 = a_end_iterator->value - a_begin_iterator->value;
    auto lambda = diam / diam2, max_lambda = lambda;
    auto min_begin_iterator = a_begin_iterator, min_end_iterator = a_end_iterator;
    //следующие случаи
    auto stop_iterator = std::prev(nodes.end());
    for (++a_begin_iterator, ++a_end_iterator; a_end_iterator != stop_iterator; a_begin_iterator++, a_end_iterator++) {
        diam = std::prev(nodes.end())->value - nodes.begin()->value;
        diam2 = a_end_iterator->value - a_begin_iterator->value;
        lambda = diam / diam2;
        if (lambda > max_lambda) {
            max_lambda = lambda;
            min_begin_iterator = a_begin_iterator;
            min_end_iterator = a_end_iterator;
        }
    }
    //Последний случай
    diam = std::prev(a_begin_iterator)->value - nodes.begin()->value;
    diam2 = a_end_iterator->value - a_begin_iterator->value;
    lambda = diam / diam2;
    if (lambda > max_lambda) {
        max_lambda = lambda;
        min_begin_iterator = a_begin_iterator;
        min_end_iterator = a_end_iterator;
    }

    std::cout << max_lambda << std::endl;
    for (auto iter = nodes.begin(); iter != min_begin_iterator; iter++)
        std::cout << iter->value << ' ';
    for (auto iter = std::next(min_end_iterator); iter != nodes.end(); iter++)
        std::cout << iter->value << ' ';
    return 0;
}