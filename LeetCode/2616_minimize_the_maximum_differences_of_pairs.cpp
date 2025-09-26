#include <vector>
#include <climits>
#include <algorithm>

//TODO: Там делается как-то через двоичный поиск
//TODO: Потом решу эту задачу, для начала пойду немного поизучаю задачи на двоичный поиск
/*

*/

class Solution {
    public:
        int minimizeMax(std::vector<int>& nums, int p) {
            /*
            Итак, нужно найти p пар индексов таких, что максимальная абсолютная разность среди этих пар была минимальна
            Вернуть соостветственно эту минимальную разность
            Итак, предполагаю, что 
            1)массивы в начале надо отсортировать по убыванию или возрастанию
            2)жадным способом сохраняем последние 2 состояния dp[k] (+1 текущее), при котором сохраняется минимальный максимум разностей k пар

            TODO: Внезапно, мой жадный способ не проходит по времени выполнения


            Они как-то это делают через двоичный поиск
            Допустим, можно сделать так
            */
            std::vector<std::vector<int>> dp(3, std::vector<int>(p + 1, INT_MAX));
            dp[0][0] = dp[1][0] = dp[2][0] = 0; 
            int diff = 0;
            std::sort(nums.begin(), nums.end());
            for (int i = 1, i_end = nums.size(); i < i_end; ++i) {
                diff = std::abs(nums[i]-nums[i-1]);
                for (int k = std::min(p,(i + 2) / 2); k >= 1; --k) {
                    dp[0][k] = std::min(std::max(diff, dp[2][k-1]), dp[1][k]);
                }
                std::swap(dp[1], dp[2]);
                std::swap(dp[0], dp[1]);
            }
            return dp[1][p];
        }
    };

#include <iostream>

int main(void) {
    std::vector<int> nums1 {10,1,2,7,1,3}, nums2 {4,2,1,2}, nums3 {4,0,2,1,2,5,5,3}, nums4 {3,4,2,3,2,1,2};
    Solution sol;

    std::cout << sol.minimizeMax(nums1, 2) << std::endl;
    std::cout << sol.minimizeMax(nums2, 1) << std::endl;
    std::cout << sol.minimizeMax(nums3, 3) << std::endl;
    std::cout << sol.minimizeMax(nums4, 3) << std::endl;
    return 0;
}