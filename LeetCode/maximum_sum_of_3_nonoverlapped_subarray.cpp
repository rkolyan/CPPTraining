#include <vector>
#include <iostream>
#include <numeric>


//SUCCESS, но можно сделать решение с меньшим количеством памяти, правда оно вряд ли будет производительнее этого
class Solution {
    private:
        inline void update(std::vector<int> &dp, std::vector<int> &i, int index, int new_value, int prev_value) {
            if (new_value > prev_value) {
                dp[index] = new_value;
                i[index] = index; 
            } else {
                dp[index] = prev_value;
                i[index] = i[index-1];
            }
        }
    public:
        std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
            /*
            Итак, нужно вернуть индексы начала 3-х непересекающихся подмассивов размером k с максимальной суммой
            Как вариант вычислять префиксы в начале префиксы k-х сумм
            a1,      a2,      a3,...,an
            a1+a2+a3,a2+a3+a4,....
            Или дерево отрезков
            Берём находим максимальный по размеру суммы индекс
            Смотрим оставшиеся отрезки слева и справа, в одном из них осуществляем поиск следующей по размеру суммы
            в оставшихся 3 отрезках ищем последний k-массив
            Просматривая текущий k - подмассив следует его проверить, вдруг он пересекает возможные 2 более более выгодных k-подмассива
            Тогда стоит строить 2 дерева отрезков
            Хотя, для вставки выгодней строить корневую декомпозицию

            А зачем, берём очередь приоритетов и в ней храним 2k+1 индексы
            
            Создаем массив префиксов сумм
            dp1[i] = максимальная сумма из k 
            dp1[i] = max(dp1[i-1], p[i])
            dp2[i] = max(dp2[i-1], dp1[i-k] + p[i])
            dp3[i] = max(dp3[i-1], dp2[i-k] + p[i])
            i1[i] = k1;
            i2[i] = k2;
            i3[i] = k3;
            Аналогично храним индексы
            */
            std::vector<int> dp1(nums.size()), dp2(nums.size()), dp3(nums.size()), i1(nums.size()), i2(nums.size()), i3(nums.size());
            int curr_sum = std::accumulate(nums.begin(), std::next(nums.begin(), k), 0), tmp_dp1 = 0, tmp_dp2 = 0;
            int last_i = 2 * k;
            dp1[k-1] = curr_sum;
            i1[k-1] = k-1;
            for (int i = k; i < last_i; ++i) {
                curr_sum += nums[i] - nums[i-k];
                update(dp1, i1, i, curr_sum, dp1[i-1]);
            }
            dp2[last_i - 1] = dp1[k-1] + curr_sum;
            i2[last_i - 1] = last_i-1;
            last_i  = 3 * k;
            for (int i = 2 * k; i < last_i; ++i) {
                curr_sum += nums[i] - nums[i-k];
                update(dp1, i1, i, curr_sum, dp1[i-1]);
                update(dp2, i2, i, dp1[i-k] + curr_sum, dp2[i-1]);
            }
            dp3[last_i - 1] = dp2[2 * k - 1] + curr_sum;
            i3[last_i - 1] = last_i - 1;
            for (int i = last_i; i < nums.size(); ++i) {
                curr_sum += nums[i] - nums[i-k];
                update(dp1, i1, i, curr_sum, dp1[i-1]);
                update(dp2, i2, i, dp1[i - k] + curr_sum, dp2[i-1]);
                update(dp3, i3, i, dp2[i - k] + curr_sum, dp3[i-1]);
            }
            std::vector<int> result;
            result.resize(3);
            auto index = i3[nums.size()-1] - k + 1;
            result[2] = index;
            index = i2[index - 1] - k + 1;
            result[1] = index;
            index = i1[index - 1] - k + 1;
            result[0] = index;
            return result;
        }
    };
int main(void) {
    std::vector<int> nums1 = {1,2,1,2,6,7,5,1}, nums2 = {1,2,1,2,1,2,1,2,1},
    nums3 = {0, 21, 22, 9, 29, 9, 23, 13, 20, 14, 24, 30, 6, 17, 26, 24, 15, 1, 14, 15}, 
    nums4 = {7,13,20,19,19,2,10,1,1,19};
    int k1 = 2, k2 = 2;
    Solution sol;
    auto result = sol.maxSumOfThreeSubarrays(nums1, k1);
    std::cout << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
    result = sol.maxSumOfThreeSubarrays(nums2, k2);
    std::cout << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
    result = sol.maxSumOfThreeSubarrays(nums3, 4);
    std::cout << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
    result = sol.maxSumOfThreeSubarrays(nums4, 3);
    std::cout << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
    return 0;
}