#include <vector>
#include <climits>

//SUCCESS, 100%, 0ms, было просто...

/*
Дан массив массивов, где каждый подмассив - строка в треугольнике
Пример: {{2},{3,4},{6,5,7},{4,1,8,3}}
Треугольник:
    2
   3 4
  6 5 7
 4 1 8 3

Нужно найти наименьшую сумму пути (для каждого элемента предыдущей строки выбираем только соседние элементы справа и слева от него на следующей строке, ну, понял)
//TODO: Надо бы поработать над качественными формулировками
*/

/*
Алгоритм явно dp
dp1[i] = std::max(dp2[i-1], dp2[i]) + arr[i]
*/



class Solution {
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) {
        //Пофигу на аллокатор
        std::vector<int> dp1, dp2;
        dp1.reserve(triangle.size());
        dp2.reserve(triangle.size());
        dp1.push_back(triangle[0][0]);
        dp2.push_back(0);
        for (int i = 1; i < triangle.size(); ++i) {
            dp2[0] = triangle[i][0] + dp1[0];
            for (int j = 1; j < i; ++j) {
                dp2[j] = std::min(dp1[j-1], dp1[j]) + triangle[i][j];
            }
            dp2.push_back(dp1.back() + triangle[i].back());
            std::swap(dp1, dp2);
            dp2.push_back(0);//Это просто расширить dp2 заранее
        }
        int minlen = INT_MAX;
        for (const auto &len : dp1) {
            minlen = std::min(minlen, len);
        }
        return minlen;
    }
    //Вообще так делать нельзя, но мне заколебало прописывать для каждого тестового случая отдельную переменную
    int minimumTotal(std::vector<std::vector<int>> &&triangle) {
        return minimumTotal(triangle);
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::cout << sol.minimumTotal({{2},{3,4},{6,5,7},{4,1,8,3}}) << std::endl;
    return 0;
}

