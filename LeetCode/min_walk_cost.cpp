#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

typedef unsigned int bit_count_t;
typedef int edge_t;
typedef unsigned int index_t;
using coord_t = std::pair<index_t, index_t>;
using uv_t = std::tuple<bit_count_t, edge_t, coord_t>;

class Solution {
    private:
        bit_count_t findBitCount(edge_t num) {
            bit_count_t count = 0;
            while (num != 0) {
                if (num & 1) {
                    ++count;
                }
                num >>= 1;
            }
            return count;
        }
    public:
        std::vector<int> minimumCost(int n, std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& query) {
            std::vector<uv_t> container;
            container.reserve(n);
            bit_count_t bit_count = 0;
            index_t begin, end = 0;
            std::priority_queue<uv_t, std::vector<uv_t>, std::greater<uv_t>> pq(std::greater<uv_t>(), std::move(container));
            for (unsigned int i = 0; i < n; ++i) {
                begin = edges[i][0];
                end = edges[i][1];
                bit_count = edges[i][2];
                pq.emplace(bit_count, edges[i][0], begin, end);
            }
            /*
            Итак, мы можем заранее сохранять предполагаемое количество вершин
            Нам в любом случае надо сохр
            Я так понял нам в любом случае придётся строить множество непересекающих множеств
            Наверное, вместе с этим необходимо будет учитывать произведение

            Итак, допустим
            a - b = 0010
            b - c = 0011
            a - c = 1100
            Самое маленькое значение между b->с минимальный обход через b->a и a->c (результатом будет 0)
            Но если сравнивать по количеству единиц, то сначала будет 0010 потом 0011 и результат
            Но в случае минимальное расстоянием между a->c будет 1100, а могло быть 0010

            Таким образом в любом случае нам придётся для каждой отдельной вершины использовать алгоритм Дейкстры
            При этом результаты можно кэшировать, чтобы 
            
            Таким образом в начале ищем компоненты связности
            */
            
            return {};
        }
    };