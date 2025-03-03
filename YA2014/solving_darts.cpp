//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <vector>

int main() {
    unsigned int N = 0, M = 0;
    std::cin >> N >> M;
    std::vector<std::vector<unsigned int>> matr;
    matr.resize(N+2);
    matr[0].resize(M+2);
    matr[N+1].resize(M+2);
    for (unsigned int j = 1; j <= M; j++) {
        matr[0][j] = matr[N+1][j] = 0;
    }
    for (unsigned int i = 1; i <= N; i++) {
        matr[i].resize(M+2);
        matr[i][0] = matr[i][M+1] = 0;
        for (unsigned int j = 1; j <= M; j++) {
            std::cin >> matr[i][j];
        }
    }

    double maximum = 0, tmp = 0, m_i = 1, m_j = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            tmp = 0.5 * matr[i][j] + 0.0625 * (matr[i - 1][j - 1] + matr[i-1][j] + matr[i-1][j+1] + matr[i][j+1] + matr[i+1][j+1] + matr[i+1][j] + matr[i+1][j-1] + matr[i][j-1]);
            if (tmp > maximum) {
                maximum = tmp;
                m_i = i;
                m_j = j;
            }
        }
    }
    std::cout << m_i << " " << m_j;
    return 0;
}