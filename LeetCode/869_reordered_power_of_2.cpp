#include <vector>

//SUCCESS 0ms, win 100%, эм, и кажется у меня реально самое быстрое решение, там у самых быстрых скорость 1 ms...
class Solution {
public:
    bool reorderedPowerOf2(int n) {
        
        /*
        Итак, мы должны определить, не является ли число степенью 2-ки если поменять его числа местами
        допустим есть число 2401 из него можно собрать 1024, что есть степень 2ки
        1 = 1
        10 = 1010
        100 = 64 + 32 + 4 = 01100100
        1000 = 512 + 256 + 128
        Ну, допустим для каждой степени 2-ки будем определять все цифры которые в него войдут
        */
        int nums[32][10] = {0}, counts[32] = {0}, digits[10] = {0}, digit_count = 0;
        int index = 0;
        bool flag = false;
        unsigned cur_num;
        for (unsigned int bit = 1, i = 0; i < 32; bit <<= 1, ++i) {
            cur_num = bit;
            while (cur_num) {
                ++nums[i][cur_num % 10];
                ++counts[i];
                cur_num /= 10;
            }
        }
        while (n) {
            ++digits[n % 10];
            ++digit_count;
            n /= 10;
        }

        for (; index < 32 && digit_count > counts[index]; ++index);
        for (; index < 32 && digit_count == counts[index]; ++index) {
            flag = true;
            for (int i = 0; i < 10; ++i) {
                if (nums[index][i] != digits[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        return flag;
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::cout << sol.reorderedPowerOf2(2401) << std::endl;
    std::cout << sol.reorderedPowerOf2(215) << std::endl;
    std::cout << sol.reorderedPowerOf2(11) << std::endl;
    return 0;
}