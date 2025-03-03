//
// Created by rkolyan on 17.09.2024.
//

#include <set>
#include <iostream>

int input_numbers(int &N, std::set<int> &numbers) {
    int tmp = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> tmp;
        numbers.insert(tmp);
    }
    return 0;
}

int output_result(const double result, const std::set<int> &A) {
    std::cout << result << std::endl;
    for (const auto &element : A) {
        std::cout << element << " ";
    }
}

double find_max_pseudo_size(const int N, const std::set<int> &numbers, std::set<int> &A) {
    auto begin = numbers.begin(), end = std::next(begin, N / 2), max_begin = begin, max_end = end;
    int diamA = 0, diamSA = 0;
    double lambda, max_lambda = 0;
    while (end != numbers.end()) {
        auto prev = std::prev(numbers.end());
        diamSA = *end - *begin;
        if (begin != numbers.begin()) {
            if (prev != end) {
                diamA = *prev - *numbers.begin();
            } else {
                diamA = *std::prev(begin) - *numbers.begin();
            }
        } else {
            diamA = *prev - *std::next(end);
        }
        lambda = static_cast<double>(diamA) / static_cast<double>(diamSA);
        if (max_lambda < lambda) {
            max_lambda = lambda;
            max_begin = begin;
            max_end = end;
        }
        begin++;
        end++;
    }
    A.insert(numbers.begin(), max_begin);
    A.insert(std::next(max_end), numbers.end());
    return max_lambda;
}

int main(void) {
    int N = 0;
    std::set<int> numbers, A;
    input_numbers(N, numbers);
    auto result = find_max_pseudo_size(N, numbers, A);
    output_result(result, A);
    return 0;
}