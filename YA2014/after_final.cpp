#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <stack>
#include <map>

//почти SUCCESS
//падает на 7-м тесте в связи с превышением по времени
//у меня простой поиск 
//

/*
    
*/

using vertice_t = unsigned int;
using path_t = unsigned int;
using index_t = unsigned int;
using count_t = int;
enum class Mark {
    UNMARKED,
    MARKED
};

//Быстрая реализация (На основе алгоритма дейкстры)
void find_longes_shortest_iterative3(const std::vector<std::vector<std::pair<vertice_t, path_t>>> &vertices, count_t &max_count, path_t &min_path_len) {
    //TODO: 1)Инициализируем массив весов
    std::vector<std::pair<path_t, count_t>> weights(vertices.size());
    auto iter = weights.begin();
    *iter = std::pair<path_t, count_t>(UINT_MAX, 0);
    std::fill(std::next(iter), weights.end(), std::pair<path_t, count_t>(UINT_MAX, 0));
    for (vertice_t _tmp = 0; _tmp < vertices.size(); _tmp++) {
        /*
        Алгоритм следующий:
        Ищем вершину с наименьшим путем и весом (v)
        Помечаем её,
        Далее выбираем subvector[v], и для каждого её элемента

        */
    }
}
//Тоже медленная (падает на 11-м тесте)
//TODO: Надо бы у стека allocator поменять для того, чтоб память не выделять много раз
void find_longes_shortest_iterative2(const std::vector<std::vector<std::pair<vertice_t, path_t>>> &vertices, count_t &max_count, path_t &min_path_len) {
    std::vector<Mark> marks;
    std::vector<std::pair<path_t, count_t>> weights;
    std::stack<std::pair<vertice_t, index_t>> stack;
    /*
        Итак, для каждой вершины добавляем вес - минимальное расстояние, за которой можно до неё дойти
        Когда мы каждый раз доходим до вершины из пути, то мы сравниваем текущий путь с весов вершины,
        если вес вершины меньше, то сбрасываем стек (поиск не имеет смысла), если вес вершины равен, то
        сравниваем с количеством дорог (вес вершины состоит из расстояния и количества дорог), если вес
        вершины больше, то обновляем вес текущими значениями и идём дальше от этой вершины.
    */
    bool onEnter = true;
    count_t count = 0;
    path_t path_len = 0;

    marks.resize(vertices.size());
    weights.resize(vertices.size());
    std::fill(marks.begin(), marks.end(), Mark::UNMARKED);
    std::fill(weights.begin(), weights.end(), std::pair<path_t, count_t>(UINT_MAX, 0));
    stack.emplace(0, 0);
    while (!stack.empty()){
        if (onEnter) {
            const auto &curr_index = stack.top().first;
            marks[curr_index] = Mark::MARKED;
            auto &curr_weight = weights[curr_index];
            if (path_len < curr_weight.first || (path_len == curr_weight.first && count >= curr_weight.second)) {
                curr_weight = std::pair<path_t, count_t>(path_len, count);
                auto &neighbour_index = stack.top().second;
                const auto neigbours = vertices[curr_index];
                bool flag = true;
                while (neighbour_index < neigbours.size() && flag) {
                    auto next_path = neigbours[neighbour_index];
                    if (marks[next_path.first] == Mark::UNMARKED) {
                        flag = false;
                        count++;
                        path_len += next_path.second;
                        stack.emplace(next_path.first, 0);
                    } else {
                        neighbour_index++;
                    }
                }
                if (flag) {
                    onEnter = false;
                }
            } else {
                onEnter = false;
            }
        } else {
            marks[stack.top().first] = Mark::UNMARKED;
            stack.pop();
            if (!stack.empty()) {
                count--;
                path_len -= vertices[stack.top().first][stack.top().second].second;
                stack.top().second++;
            }
            onEnter = true;
        }
    }
    min_path_len = weights[weights.size() - 1].first;
    max_count = weights[weights.size() - 1].second;
}

//Старая более медленная версия
void find_longes_shortest_iterative(const std::vector<std::vector<std::pair<vertice_t, path_t>>> &vertices, std::size_t &max_count, path_t &min_path_len) {
    std::vector<Mark> marks;
    std::stack<std::pair<vertice_t, index_t>> stack;
    bool onEnter = true;
    std::size_t count = 0;
    path_t path_len = 0;
    vertice_t last = vertices.size() - 1;

    min_path_len = ~static_cast<path_t>(0);
    max_count = 0;
    marks.resize(vertices.size());
    std::fill(marks.begin(), marks.end(), Mark::UNMARKED);
    stack.emplace(0, 0);
    while (!stack.empty()){
        if (onEnter) {
            const auto &curr_index = stack.top().first;
            marks[curr_index] = Mark::MARKED;
            auto &neighbour_index = stack.top().second;
            const auto neigbours = vertices[curr_index];
            bool flag = true;
            if (curr_index != last) {
                while (neighbour_index < neigbours.size() && flag) {
                    auto next_path = neigbours[neighbour_index];
                    if (marks[next_path.first] == Mark::UNMARKED) {
                        flag = false;
                        count++;
                        path_len += next_path.second;
                        stack.emplace(next_path.first, 0);
                    } else {
                        neighbour_index++;
                    }
                }
                if (flag) {
                    onEnter = false;
                }
            } else {
                if (path_len < min_path_len) {
                    min_path_len = path_len;
                    max_count = count;
                } else if (path_len == min_path_len && count > max_count) {
                    max_count = count;
                }
                onEnter = false;
            }
        } else {
            marks[stack.top().first] = Mark::UNMARKED;
            stack.pop();
            if (!stack.empty()) {
                count--;
                path_len -= vertices[stack.top().first][stack.top().second].second;
                stack.top().second++;
            }
            onEnter = true;
        }
    }
}

std::vector<std::vector<std::pair<vertice_t, path_t>>> input_graph() {
    std::vector<std::vector<std::pair<vertice_t, path_t>>> vertices;
    std::size_t N, M;
    
    std::cin >> N >> M;
    vertices.resize(N);
    vertice_t a, b;
    path_t c;
    for (auto &vertice : vertices) {
        vertice.reserve(M);
    }
    std::map<std::pair<vertice_t, vertice_t>, path_t> paths;
    for (std::size_t i = 0; i < M; i++) {
        std::cin >> a >> b >> c;
        const std::pair<vertice_t, vertice_t> index1{a-1, b-1}, index2{b-1, a-1};
        auto iter1 = paths.find(index1);
        auto iter2 = paths.find(index2);
        if (iter1 != paths.cend()) {
            if ((*iter1).second > c) {
                (*iter1).second = c;
                (*iter2).second = c;
            }
        } else {
            paths[index1] = c;
            paths[index2] = c;
        }
    }
    for (const auto &path : paths) {
        vertices[path.first.first].emplace_back(path.first.second, path.second);
    }
    return vertices;
}

std::vector<std::vector<path_t>> input_matr2() {
    std::size_t N = 0, M = 0;
    index_t a = 0, b = 0;
    path_t c = 0;

    std::cin >> N >> M;

    std::vector<std::vector<path_t>> matr(N);
    for (auto &row : matr) {
        row.resize(N);
        std::fill(row.begin(), row.end(), UINT_MAX);
    }
    for (unsigned int i = 0; i < M; i++) {
        std::cin >> a >> b >> c;   
        matr[a-1][b-1] = c;
        matr[b-1][a-1] = c;
    }
    return matr;
}

int main(void) {
    auto graph = input_matr2();
    count_t count{};
    path_t pathlen{};
    find_longes_shortest_iterative3(graph, count, pathlen);
    std::cout << pathlen << ' ' << count;
    return 0;
}