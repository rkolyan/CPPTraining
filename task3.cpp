//
// Created by rkolyan on 10.04.2024.
//

#include <iostream>
#include <vector>
#include <set>

std::vector<std::vector<int>> find_minmas(std::vector<std::vector<int>> matr, int N, int M) {
    std::set<std::pair<int, int>> queue;
    std::set<std::>
    std::vector<std::vector<int>> matr_res;
    matr_res.resize(N);
    for (int i = 0; i < N; i++){
        matr_res[i].resize(M);
    }

    for (int i = 0; i < N; i++) {
        //1)записывам в
        matr_res[i] = matr[i];
        for (int j = 0; j < N; j++) {
            if (matr[i][j] != 0 && i != j) {
                queue.emplace(i, j);
            }
        }
        while (!queue.empty()) {
            auto pair = queue.back();
            queue.pop();
            if (matr[pair.first][pair.second] > 0 && (matr_res[i][pair.second] >= matr[pair.first][pair.second] || matr_res[i][pair.second] == -1)) {
                matr_res[i][pair.second] = matr[pair.first][pair.second];
            }
        }
    }
}

void input_matr(std::vector<std::vector<int>> &matr, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> matr[i][j];
        }
    }
}

int main(void) {
    int N = 0;
    std::cin >> N;
    std::vector<std::vector<int>> matr;
    matr.resize(N);
    for (int i = 0; i < N; i++) {
        matr[i].resize(N);
    }
}