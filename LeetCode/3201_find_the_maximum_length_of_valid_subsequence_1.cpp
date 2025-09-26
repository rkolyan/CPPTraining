#include <vector>

//SUCCESS, мое решение 6 ms, 55,29% побеждает
/*
Пока в дизассемблер не гляну не пойму почему оно 0ms и быстрее моего решения, неужели std::max настолько сильно замедляет?
Хотя в этом быстром решении проверок и арифметических операций куда больше чем у меня...
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int res = 0, n = nums.size();

        int odd = 0, even = 0, alternate = 1, prev = nums[0];
        for(int i = 0; i < n; i++){
            if(nums[i] % 2 == 1) odd++;
            else even++;

            if(i >= 1 && nums[i] % 2 != prev % 2){
                alternate++;
                prev = nums[i];
            }
        }
        return max({odd, even, alternate});
    }
};
*/

class Solution {
public:
    int maximumLength(std::vector<int>& nums) {
        int count0 = 0, count1 = 0, count10 = 0, count01 = 0;
        /*
        Итак, последовательность может быть следующего типа
        либо чередоваться - четный, нечетный
        либо быть одинаковыми по четности
        тогда правило что (sub[x-1] + sub[x])%2 == (sub[x] + sub[x+1])%2 выполняется.
        тогда делаем следующее
        Мы должны
        Вот у нас есть 
        */
        for (const auto &num : nums) {
            if (num % 2) {
                ++count1;
                count01 = std::max(count10+1,count01);
            } else {
                ++count0;
                count10 = std::max(count01+1, count10);
            }
        }
        return std::max(std::max(count1, count0), std::max(count10, count01));
    }
};

#include <iostream>
int main(void) {
    Solution sol;
    std::vector<int> nums{1,2,1,1,2,1,2};
    std::cout << sol.maximumLength(nums) << std::endl;
    return 0;
}