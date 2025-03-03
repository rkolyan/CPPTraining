//
// Created by rkolyan on 10.04.2024.
//

#include <iostream>
#include <vector>
#include <array>
#include <map>

int main(void) {
    int N = 0;
    std::vector<std::array<int, 6>> cubes;
    std::map<int, int, std::less<>> counts;
    std::map<int, double, std::less<>> probs;
    std::cin >> N;
    cubes.resize(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            std::cin >> cubes[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            for (int n1 = 0; n1 < 6; n1++) {
                for (int n2 = 0; n2 < 6; n2++) {
                    counts[cubes[i][n1] + cubes[j][n2]]++;
                }
            }
        }
    }
    int all_counts = 0;
    for (const auto &[_, count] : counts) {
        all_counts += count;
    }
    for (const auto &[sum, count] : counts) {
        probs[sum] = static_cast<double>(count) / all_counts;
    }
    double result = 0;
    for (const auto &[sum, prob] : probs) {
        result += sum * sum * sum * prob;
    }
    std::cout << result;
}