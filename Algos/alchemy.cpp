//
// Created by rkolyan on 13.09.2024.
//

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include <set>

class Ingridients {
private:
    struct vertice_t {
        int A_count;
        int B_count;
        bool calculated;
        bool working;
        std::map<int, int> next;
    };
    std::vector<vertice_t> vertices;

public:
    void resize(int N) {
        vertices.resize(N-2);
    }
    void setElement(int index, const std::vector<int> &ings) {
        for (const auto &ing : ings) {
            if (ing == 1) {
                vertices[index].A_count++;
            } else if (ing == 2) {
                vertices[index].B_count++;
            } else {
                vertices[index].next[ing-3]++;
            }
            vertices[index].calculated = false;
            vertices[index].working = false;
        }
    }
    void calculateIngridients() {
        std::list<size_t> v_next;
        std::set<size_t> v_used;
        for (size_t i = 0; i < vertices.size(); i++) {
            v_used.insert(i);
            for (const auto &vertice : vertices[i].next) {
                if (v_used.find(vertice))
            }
        }
    }
};

int main() {
    int N = 0;
    Ingridients ingridients;

    std::cin >> N;
    ingridients.resize(N);
}