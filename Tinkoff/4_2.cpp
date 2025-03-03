//
// Created by rkolyan on 27.01.2025.
//

#include <iostream>
#include <vector>
#include <cmath>

int main(void) {
    std::size_t N = 0;
    double R = 0.0, max_sqr = 0.0, alpha = 0.0, a = 0.0, b = 0.0, c = 0.0, p = 0.0;
    std::vector<double> sums;
    std::vector<unsigned int> indexes;
    std::size_t pos1 = 0, pos2 = 0, pos3 = 0, diff1 = 0, diff2 = 0, diff3 = 0;
    std::cin >> N;
    sums.resize(N+1);
    R = sqrt(1.0 / (2.0 * (1.0 - cos(M_PI / static_cast<double>(N)))));
    sums[0] = 0.0;
    sums[1] = 0.0;
    sums[2] = 0.0;
    for (std::size_t size = 3; size <= N; size++) {
        max_sqr = 0.0;
        for (pos1 = 0; pos1 < size; pos1++) {
            for (pos2 = pos1 + 1; pos2 < size; pos2++) {
                for (pos3 = pos2 + 1; pos3 < size; pos3++) {
                    diff1 = pos2 - pos1 - 1;
                    diff2 = pos3 - pos2 - 1;
                    diff3 = size - pos3 + pos1 - 1;
                    alpha = M_PI / static_cast<double>(N) * static_cast<double>(std::min(pos2 - pos1, pos1 + size - pos2));
                    a = R * sqrt(2 * (1 - cos(alpha)));
                    alpha = M_PI / static_cast<double>(N) * static_cast<double>(std::min(pos3 - pos2, pos2 + size - pos3));
                    b = R * sqrt(2 * (1 - cos(alpha)));
                    alpha = M_PI / static_cast<double>(N) * static_cast<double>(std::min(pos3 - pos1, pos1 + size - pos3));
                    c = R * sqrt(2 * (1 - cos(alpha)));
                    p = (a + b + c) / 2;
                    max_sqr = std::max(max_sqr, sqrt(p * (p - a) * (p - b) * (p - c)) + sums[diff1] + sums[diff2] + sums[diff3]);
                }
            }
        }
        sums[size] = max_sqr;
    }
    std::cout << sums[N];
    return 0;
}