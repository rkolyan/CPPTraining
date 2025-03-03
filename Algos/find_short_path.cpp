//
// Created by rkolyan on 12.09.2024.
//

#include <list>
#include <set>
#include <queue>
#include <map>
#include <iostream>

using number_t = std::size_t;

int find_short_path(const std::vector<std::vector<int>> &graph, const number_t begin, const number_t end) {
    number_t current = begin;
    int count = 0;
    std::pair<number_t, int> vert;
    std::set<number_t> vertice_used;
    std::queue<std::pair<number_t, int>> vertice_queue;

    vertice_queue.emplace(begin, 0);
    vertice_used.insert(begin);
    do {
        vert = vertice_queue.front();
        current = vert.first;
        count = vert.second;
        for (std::size_t i = 0; i < graph[current].size(); i++) {
            if (vertice_used.find(graph[current][i]) == vertice_used.end()) {
                vertice_used.insert(graph[current][i]);
                vertice_queue.emplace(graph[current][i], count + 1);
            }
        }
        vertice_queue.pop();
    } while (current != end);
    return count;
}

int create_graph(std::vector<std::vector<int>> &graph, const std::vector<int> &islands) {
    std::map<number_t, std::set<int>> portals;

    graph.clear();
    graph.resize(islands.size());
    for (int i = 0; i < islands.size(); i++) {
        portals[islands[i]].insert(i);
    }
    if (graph.size() > 1) {
        graph[0].push_back(1);
        for (const auto &number : portals[islands[0]]) {
            if (number != 0 && number != 1)
                graph[0].push_back(number);
        }
    }
    for (std::size_t i = 1; i < islands.size() - 1; i++) {
        graph[i].push_back(i-1);
        graph[i].push_back(i+1);
        for (const auto &number : portals[islands[i]]) {
            if (number != i-1 && number != i && number != i+1)
                graph[i].push_back(number);
        }
    }
    if (graph.size() > 2) {
        graph[graph.size()-1].push_back(graph.size()-2);
        for (const auto &number : portals[islands[graph.size()-1]]) {
            if (number != graph.size()-1 && number != graph.size()-2)
                graph[graph.size()-1].push_back(number);
        }
    }
    return 0;
}

int main(void) {
    std::size_t n = 0;
    std::vector<int> islands;
    std::vector<std::vector<int>> graph;

    std::cin >> n;
    islands.resize(n);
    for (std::size_t i = 0; i < n; i++) {
        std::cin >> islands[i];
    }
    create_graph(graph, islands);
    std::cout << find_short_path(graph, 0, graph.size()-1);
}