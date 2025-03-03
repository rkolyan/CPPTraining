//
// Created by rkolyan on 31.05.2024.
//

#include <cstdint>
#include <vector>
#include <stack>
#include <iostream>
#include <list>
#include <algorithm>

using index_t = uint32_t;
using number_t = uint32_t;

void print_vector(const std::vector<number_t> &numbers) {
    for (const auto &element : numbers) {
        std::cout << element << " ";
    }
    std::cout << ":end" << std::endl;
}

uint64_t find_counts_arrays(const uint32_t &m, const uint32_t &n) {
    uint64_t count = 0;
    index_t index = 0;
    number_t number = m;
    bool flag = true;
    std::vector<number_t> numbers;
    numbers.resize(n);
    for (uint32_t i = 0; i < n; i++) {
        numbers[i] = 0;
    }
    std::stack<std::pair<index_t, number_t>> num_stack;
    do {
        flag = false;
        if (index >= n) {
            if (number > 1) {
                index = 0;
                number--;
            } else {
                number = num_stack.top().second;
                index = num_stack.top().first;
                numbers[index] = 0;
                index++;
                num_stack.pop();
            }
        }
        while (index < n) {
            if (numbers[index] == 0) {
                flag = true;
                numbers[index] = number;
                num_stack.emplace(index, number);
                index += number;
            } else {
                 index++;
            }
        }
        if (flag && numbers.size() == num_stack.size()) {
            count++;
            //print_vector(numbers);
        }
    } while (!(num_stack.empty() && index >= n && number == 1));
    return count;
}

long double sum_coeffs(const std::vector<uint64_t> &x, const index_t &prohibited_index, const uint32_t &number) {
    std::list<index_t> indexes;
    index_t index = 0;
    long double result = 0, tmp = 0;

    do {
        if (!indexes.empty()) {
            do {
                index = indexes.front() + 1;
                indexes.pop_front();
            } while (index >= number && !indexes.empty());
        }
        while (indexes.size() != number && index < x.size()) {
            if (index != prohibited_index) {
                indexes.push_front(index);
            }
            index++;
        }
        tmp = 1;
        for (const auto &ind: indexes) {
            tmp *= x[ind];
        }
        result += tmp;
    } while (indexes.size() != number);
    if (number % 2 - 1) {
        return result;
    }
    return - result ;
}

std::vector<long double> find_coeffs(const std::vector<uint64_t> &x, const std::vector<uint64_t> &y, const size_t &count) {
    std::vector<long double> a, a_result;
    long double tmp = 0;
    a.resize(count);
    a_result.resize(count);

    a[0] = 0;
    for (index_t i = 1; i <= count; i++) {
        a[i] = static_cast<long double>(y[i]) / x[i];
        tmp = 1;
        for (index_t j = 0; j <= count; j++) {
            if (i != j) {
                tmp *= static_cast<long double>(x[i]) - x[j];
            }
        }
        a[i] /= tmp;
    }

    for (index_t i = 0; i <= count; i++) {
        a_result[i] = 0;
    }

    for (index_t i = 1; i <= count; i++) {
        a_result[i] += a[i];
    }

    for (index_t i = 1; i <= count; i++) {
        for (index_t j = 1; j <= count; j++) {
            a_result[i] += a[j] * sum_coeffs(x, j, i);
        }
    }
    return a_result;
}

long double calculate_function(const long double &x, const std::vector<long double> &a, number_t count) {
    long double result = 0;
    long double tmp_x = 1;
    for (int number = static_cast<int>(count); number >= 0; number--) {
        result += tmp_x * a[number];
        tmp_x *= x;
    }
    return result;
}

#define N_max 10

int main(void) {
    std::vector<uint64_t> y_array, x_array;
    x_array.resize(N_max + 1);
    y_array.resize(N_max + 1);
    x_array[0] = y_array[0] = 0;
    for (number_t n = 1; n <= N_max; n++) {
        x_array[n] = n;
        y_array[n] = find_counts_arrays(3, n);
        std::cout << n << ":\t" << y_array[n] << std::endl;
    }
    auto a_result = find_coeffs(x_array, y_array, N_max);
    for (const auto &x : x_array) {
        std::cout << x << ":\t" << calculate_function(static_cast<long double>(x), a_result, N_max) << std::endl;
    }
    //(x0, y0), (x1, y1), (x2, y2)
    return 0;
}