//
// Created by rkolyan on 09.09.2024.
//

#include <iostream>
#include <stack>
#include <vector>


typedef short number_t;

//1. Создать и заполнить матрицу
int create_matr(number_t &N, number_t &M, std::vector<number_t> &matr) {
    std::cin >> N >> M;

    matr.resize(N*N);
    for (number_t i = 0; i < N; i++) {
        for (number_t j = 0; j < N; j++) {
            matr[i * N + j] = -1;
        }
    }

    number_t a, b, c;
    for (number_t l = 0; l < M; l++) {
        std::cin >> a >> b >> c;
        matr[(a - 1) * N + (b - 1)] = c;
        matr[(b - 1) * N + (a - 1)] = c;
    }
    return 0;
}

struct vertice_t {
    number_t num;
    number_t counter;
    number_t path_len;
};

//2. Найти путь из вершины с номером begin в вершину с номером end
std::pair<number_t, number_t> find_shortest_way(const number_t &begin, const number_t &end, const number_t &N, const std::vector<number_t> matr) {
    number_t P = 0, min_P = -1, Q = 0, maxQ = 0;
    std::vector<number_t> indicators;
    indicators.resize(N);
    std::stack<vertice_t> path;

    for (number_t i = 0; i < N; i++)
        indicators[i] = false;
    indicators[begin] = true;
    path.push(vertice_t{begin, 0, 0});
    while (!path.empty()) {
        auto &vertice = path.top();

        if (vertice.counter == N) {//Выход за границу
            path.pop();
        } else if (vertice.num == end) {//Проверка, что достигли до конечной точки
            P = vertice.path_len;
            Q = static_cast<number_t>(path.size())- 1;
            if (min_P == -1 || min_P > P) {
                min_P = P;
                maxQ = Q;
            } else if (min_P == P && Q > maxQ) {
                maxQ = Q;
            }
            indicators[end] = false;
            path.pop();
        } else if (indicators[vertice.counter]) {//Проверка наличия в списке
            vertice.counter++;
        } else if (vertice.counter != vertice.num && matr[vertice.num * N + vertice.counter] != -1) {
            path.push(vertice_t{vertice.counter, 0, static_cast<number_t>(vertice.path_len + matr[vertice.num * N + vertice.counter])});
            indicators[vertice.counter] = true;
            vertice.counter++;
        } else {
            vertice.counter++;
        }
    }
    return std::pair<number_t, number_t>{min_P, maxQ};
}

int output_matr(const std::pair<number_t, number_t> &PQ_pair) {
    std::cout << PQ_pair.first << ' ' << PQ_pair.second;
    return 0;
}

int main() {
    number_t N, M;
    std::vector<number_t> matr;
    create_matr(N, M, matr);
    auto result = find_shortest_way(0, N-1, N, matr);
    output_matr(result);
    return 0;
}