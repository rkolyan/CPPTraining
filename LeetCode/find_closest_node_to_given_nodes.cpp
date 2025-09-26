#include <iostream>
#include <vector>
#include <climits>

//SUCCESS

class Solution {
    private:
        void fill_dp(std::vector<int> &dp, const std::vector<int> &edges, int node) {
            dp.resize(edges.size(), -1);
            int current = node;
            int counter = 0;
            do {
                dp[current] = counter;
                ++counter;
                current = edges[current];
            } while (current != -1 && dp[current] == -1);
        }
    public:
        int closestMeetingNode(std::vector<int>& edges, int node1, int node2) {
            /*
            Задача следующая - edges - массив, означающий присутствие ребра от вершины i до edges[i], если edges[i] нет, то ребро не соединено,
            я так понял из каждой вершины может быть только один выход,
            Задача найти такую вершину t, при которой минимален максимум расстояний от node1 до t и от node2 до t
            Как решить такую задачу? Вроде обычным алгоритмом Дейкстры, к тому же из одной вершины может быть только 1 выход
            Наверняка тут можно состряпать даже более быстрое решение, а именно, составим 2 массива dp[edges.size()] и начнём проходится
            от node1 до до конца, аналогично node2, пока не будет достигнут конец, или пока вершина не будет уже записана
            */
            std::vector<int> dp1, dp2;
            int min_maximum = INT_MAX, maximum = 0, min_maximum_index = -1;
            fill_dp(dp1, edges, node1);
            fill_dp(dp2, edges, node2);
            for (int i = 0; i < edges.size(); ++i) {
                if (dp1[i] != -1 && dp2[i] != -1) {
                    maximum = std::max(dp1[i], dp2[i]);
                    if (min_maximum > maximum) {
                        min_maximum_index = i;
                        min_maximum = maximum;
                    }
                }
            }
            return min_maximum_index;
        }
    };

int main(void) {
    std::vector<int> edges1 = {2,2,3,-1}, edges2 = {1,2,-1}, edges3 = {1, 2, 3, 4, 5, 6, 0, 2};
    Solution sol;
    std::cout << sol.closestMeetingNode(edges1, 0, 1) << std::endl;
    std::cout << sol.closestMeetingNode(edges2, 0, 2) << std::endl;
    std::cout << sol.closestMeetingNode(edges3, 6, 7) << std::endl;
    return 0;    
}