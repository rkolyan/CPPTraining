#include <vector>
#include <queue>

/*
Моё решение медленное, победило лишь 13%, 141 ms, мда, как же мне впадлу искать оптимизации для каджой задачки
Вот решение, которое вроде как 0ms, решение также использует 2 приоритетные очереди, только этот чел слишком крут, не знал, что лямбда можно вот так вставлять в качестве компараторов

#include <bits/stdc++.h>
using namespace std;
int speedUp = [] {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
        auto cap = [&](int a, int b) { return capital[a] > capital[b]; };
        auto prof = [&](int a, int b) { return profits[a] < profits[b]; };

        priority_queue<int, vector<int>, decltype(cap)> minc(cap);
        priority_queue<int, vector<int>, decltype(prof)> maxp(prof);

        for (int i = 0; i < capital.size(); ++i)
            minc.push(i);

        for (int i = 0; i < k; ++i) {
            while (!minc.empty() && capital[minc.top()] <= w) {
                maxp.push(minc.top());
                minc.pop();
            }

            if (maxp.empty())
                break;

            w += profits[maxp.top()];
            maxp.pop();
        }
        return w;
    }
};
*/

class Solution {
private:
    using profit_t = int;
    using capital_t = int;
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
        /*
        Вроде задача простая, нужно с самого начала выбирать из значений капитала с любым значением профита
        Итак, приоритет у нас должен быть по наибольшей выгоде (profit), но с ограничением по капиталу (не меньше)
        Так что в начале сортируем значения по капиталу и профиту(капитал <=, профит >=)
        */
        std::vector<std::pair<capital_t, profit_t>> mem_buf1;
        std::vector<std::pair<profit_t, capital_t>> mem_buf2;
        mem_buf1.reserve(profits.size());
        mem_buf2.reserve(profits.size());
        std::priority_queue<std::pair<capital_t, profit_t>, std::vector<std::pair<capital_t, profit_t>>, std::greater<std::pair<capital_t, profit_t>>> queue1(std::greater<std::pair<capital_t, profit_t>>{}, std::move(mem_buf1));
        std::priority_queue<std::pair<profit_t, capital_t>, std::vector<std::pair<profit_t, capital_t>>> queue2(std::less<std::pair<capital_t, profit_t>>{}, std::move(mem_buf2));
        for (std::size_t i = 0; i < capital.size(); ++i) {
            queue1.emplace(capital[i], profits[i]);
        }
        for (int i = 0; i < k; ++i) {
            while (!queue1.empty()) {
                const auto &tmp = queue1.top();
                if (tmp.first <= w) {
                    queue2.emplace(tmp.second, tmp.first);
                    queue1.pop();
                } else {
                    break;
                }
            }
            if (!queue2.empty()) {
                const auto &tmp = queue2.top();
                w += tmp.first;
                queue2.pop();
            } else {
                break;
            }
        }
        return w;
    }
};

#include <iostream>

int main(void) {
    std::vector<int> profits{1,2,3}, capital1{0,1,1}, capital2{0,1,2};
    Solution sol;

    std::cout << sol.findMaximizedCapital(2, 0, profits, capital1) << std::endl;
    std::cout << sol.findMaximizedCapital(3, 0, profits, capital2) << std::endl;
    return 0;
}