//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <vector>

int main() {
    unsigned int N = 0, diff = 0;
    int sign = 1;
    std::vector<int> array, tmp;

    std::cin >> N;
    array.resize(N);
    tmp.resize(N);

    for (unsigned int i = 0; i < N; i++) {
        std::cin >> array[i];
        tmp[i] = 0;
    }
    sign = 1;
    diff = 0;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N - i; j++) {
            tmp[j] += sign * array[j + i];
            if (abs(tmp[j]) > diff) {
                diff = abs(tmp[j]);
            }
        }
        sign = -sign;
    }

    std::cout << diff;

    return 0;
}