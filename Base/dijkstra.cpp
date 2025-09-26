#include <climits>
#include <iostream>
#include <vector>

using path_t = int;
using vertice_t = unsigned int;

//1)Ввод матрицы смежности
std::vector<std::vector<path_t>> input_matr(std::size_t N) {
    std::vector<std::vector<path_t>> matr(N, std::vector<path_t>(N));
    for (auto &row : matr) {
        for (auto &element : row) {
            std::cin >> element;
        }
    }
    return matr;
}

//2)Ввод через множество троек значений - номера вершин и значение пути между ними
std::vector<std::vector<path_t>> input_matr2(std::size_t N, std::size_t M) {
    std::vector<std::vector<path_t>> matr(N, std::vector<path_t>(N, -1));
    vertice_t begin, end;
    path_t path;
    for (unsigned int i = 0; i < M; i++) {
        std::cin >> begin >> end >> path;
    }
    matr[begin-1][end-1] = path;
    return matr;
}

///////////////////////////////////////////
//Алгоритм Дейкстры
//TODO: Используется очередь с приоритетом


int main(void) {
    std::vector<std::vector<path_t>> matr;
    std::vector<path_t> dist;
    std::size_t N = 0;

    std::cin >> N;

    matr.resize(N);
    dist.resize(N, UINT_MAX);



    return 0;    
}