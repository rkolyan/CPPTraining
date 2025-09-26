#include <iostream>
#include <vector>
#include <algorithm>

//SUCCESS, 55 ms, победил треть, гении оптимизации дрочили на использование хеш-таблицы(вернее, массива частот) и частоту появления каждого элементов. Это вроде как сортировка подсчетом называется, ну да пофиг

class Solution {
    public:
        std::vector<std::vector<int>> divideArray(std::vector<int>& nums, int k) {
            std::vector<std::vector<int>> result(nums.size() / 3, std::vector<int>(3));
            std::sort(nums.begin(), nums.end());
            for (int i = 0, i3 = 2; i3 < nums.size(); ++i, i3 += 3) {
                if (nums[i3] - nums[i3-2] > k) {
                    return {};
                }
                result[i][2] = nums[i3];
                result[i][1] = nums[i3 - 1];
                result[i][0] = nums[i3 - 2];
            }
            return result;
        }
};

int main(void) {
    return 0;
}