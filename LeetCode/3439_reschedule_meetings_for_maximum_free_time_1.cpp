#include <vector>

//SUCCESS, 0 ms, бьет 100% (хз, как ещё можно решить, если задача на перемещающееся окно)

class Solution {
public:
    int maxFreeTime(int eventTime, int k, std::vector<int>& startTime, std::vector<int>& endTime) {
        /*
        eventTime - общее время от начала до конца, k - количество встреч, которые можно переместить, startTime, endTime - время начала и конца соответственно
        Нужно найти максимально длинный период свободного времени путем передвижения максимум k встреч на временной прямой

        Итак, у нас получается фиксированное окно размера k, известно, что у нас временные промежутки не пересекаются и вроде как отсортированы по возрастанию
        тогда алгоритм следующий
        */
        int free_time = startTime[0], max_free_time = 0;
        int i = 1;
        for (; i <= k && i < startTime.size(); ++i) {
            free_time += startTime[i] - endTime[i-1];
        }
        max_free_time = free_time;
        if (i <= k) {
            max_free_time += eventTime - endTime[i-1];
        } else {
            free_time -= startTime[0];
            for (i = k + 1; i < startTime.size(); ++i) {
                free_time += startTime[i] - endTime[i-1];
                max_free_time = std::max(max_free_time, free_time);
                free_time -= startTime[i-k] - endTime[i-k-1];
            }
            free_time += eventTime - endTime[endTime.size()-1];
            max_free_time = std::max(max_free_time, free_time);
        }
        return max_free_time;
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<int> startTime1{1,3},endTime1{2,5}, startTime2{0,2,9}, endTime2{1,4,10}, startTime3{0,1,2,3,4}, endTime3{1,2,3,4,5}, startTime4{2, 6, 12}, endTime4{4, 9, 16};
    std::cout << sol.maxFreeTime(5,1, startTime1, endTime1) << std::endl;
    std::cout << sol.maxFreeTime(10,1, startTime2, endTime2) << std::endl;
    std::cout << sol.maxFreeTime(5,2, startTime3, endTime3) << std::endl;
    std::cout << sol.maxFreeTime(20,3, startTime4, endTime4) << std::endl;
    std::cout << sol.maxFreeTime(20,10, startTime4, endTime4) << std::endl;
    std::cout << sol.maxFreeTime(20,2, startTime4, endTime4) << std::endl;
    return 0;
}