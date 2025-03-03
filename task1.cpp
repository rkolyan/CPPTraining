//
// Created by rkolyan on 03.04.2024.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <stack>

template <typename T>
class MyStack {
private:
    std::vector<T> m_stack;

public:
    MyStack(size_t N) {

    }
    void push(const T &element) {
    }
};

class Statistics {
private:
    std::vector<std::vector<size_t>> counts; //Матрица NxM
    std::vector<size_t> deltas;
    std::vector<double> koeffs;
    size_t N = 0, M = 0;
public:
    Statistics(size_t N, size_t M, double minimum, double maximum) {
        counts.resize(N);
        for (size_t i = 0; i < N; i++) {
            counts[i].resize(M);
        }
        deltas.resize(M);
        koeffs.resize(M);
        std::mt19937 mt(time(nullptr));
        std::uniform_real_distribution dist(minimum, maximum);
        for (size_t i = 0; i < M; i++) {
            deltas[i] = i + 1;
            koeffs[i] = dist(mt);
        }
    };

    /*
     * def calculate(deltas: list[int], coeffs: list[float], n: int) -> (int, np.array, float, np.array, float):
    array: np.array = np.zeros(n, dtype=np.int64)
    minimum_array: np.array = []
    maximum_array: np.array = []
    stack: list[tuple] = list()
    minimum_sum = np.inf
    maximum_sum = 0
    full = 1
    index = 1
    current_pos = deltas[index - 1]
    variants_count = 0
    array[0] = deltas[0]
    stack.append((index, 0))
    while len(stack) > 0 or index <= len(deltas):
        if index > len(deltas):
            if full == len(array):
                msum = calculate_msum(stack, coeffs)
                if msum > maximum_sum:
                    maximum_sum = msum
                    maximum_array = array.copy()
                if msum < minimum_sum:
                    minimum_sum = msum
                    minimum_array = array.copy()
                variants_count += 1
                #print(" ", variants_count, " ", msum, ": ")
                #print_array(array)
                #print("\n")
            current_pos = stack[-1][1]
            index = stack[-1][0]
            array[current_pos] = 0
            current_pos = find_next(array, current_pos, 1)
            stack.pop(-1)
            full -= 1
        elif current_pos < n:
            stack.append((index, current_pos))
            array[current_pos] = deltas[index - 1]
            full += 1
            current_pos = find_next(array, current_pos, deltas[index - 1])
        elif current_pos >= n:
            current_pos = find_next(array, 0, 0)
            index += 1

    return variants_count, minimum_array, minimum_sum, maximum_array, maximum_sum
     */

    void calculate() {
        size_t min_sum = ~0;
        size_t max_sum = 0;
        size_t full = 1;
        size_t index = 1;
        size_t current_pos = deltas[0];
        std::vector<size_t> nums;
        nums.resize(N);
        nums[0] = deltas[0];

    }
    void output_result_to_file() {
        auto filename = std::to_string(N) + "_" + std::to_string(M);
        std::ofstream stream(filename);
        stream << N << M;
        for (const auto &subvector: counts) {
            for (const auto &element: subvector) {
                stream << element;
            }
            stream << '\n';
        }
        stream.close();
    }
};

int main(void) {
    size_t N = 0, M = 0;
}