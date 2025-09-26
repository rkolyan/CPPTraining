//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <vector>

int main() {
    unsigned int N = 0, diff = 0, tmp_diff = 0;
    long int sign = 1;
    std::vector<long int> array;

    std::cin >> N;
    array.resize(N);

    for (unsigned int i = 0; i < N; i++) {
        std::cin >> array[i];
    }
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N - i; j++) {
            tmp_diff = 0;
            sign = 1;
            for (unsigned int k = 0; k <= i; k++) {
                tmp_diff += sign * array[j + k];
                sign = -sign;
            }
            if (abs(tmp_diff) > diff)
                diff = abs(tmp_diff);
        }
    }

    std::cout << diff;

    return 0;
}
