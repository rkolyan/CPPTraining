#include <vector>
#include <iostream>

//SUCCESS

class Solution {
public:
    int maxScoreSightseeingPair(std::vector<int>& values) {        
        /*
        Необходимо найти 2 точки i и j, i < j, чтобы найти values[i] + values[j] + i - j
        Для каждого элемента
        находим left_prev = предыдущий максимальный values[i] + i
        находим left = равен текущему values[current] + current
        находим right = высчитываем текущий правый элемент values[current] - current и суммируем его с left_prev, если сумма больше текущей, то обновляем сумму 
        В конце итерации left_prev = std::max(left_prev, left)
        */
        int left_prev = values.front(), left = 0, right = 0, sum = 0;
        for (int i = 1; i < values.size(); ++i) {
            left = values[i] + i;
            right = values[i] - i;
            sum = std::max(left_prev + right, sum);
            left_prev = std::max(left, left_prev);
        }
        return sum;
    }
};

int main(void) {
    std::vector<int> values1 = {8,1,5,2,6}, values2 = {1, 2};
    Solution sol;
    std::cout << sol.maxScoreSightseeingPair(values1) << std::endl;
    std::cout << sol.maxScoreSightseeingPair(values2) << std::endl;
    return 0;
}