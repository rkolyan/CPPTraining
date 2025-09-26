#include <vector>
#include <iostream>

//SUCCESS

class Solution {
    public:
        std::vector<int> lexicalOrder(int n) {
            std::vector<int> result;
            result.reserve(n);
            int num = 1;
            int remind = 0;
            int last_i = 0;
            while (result.size() < n) {
                //В начале делаем подъём до максимального разряда
                while (num <= n) {
                    result.push_back(num);
                    num *= 10;
                }
                //Затем делаем спуск на 1 (потому что у нас число больше n)
                num /= 10;
                remind = num % 10;
                num -= remind;
                for (int i = remind + 1, last_i = std::min(9, n - num); i <= last_i; ++i) {
                    result.push_back(num + i);
                }
                num /= 10;
                while (num % 10 == 9) {
                    num /= 10;
                }
                ++num;
            }
            return result;
        }
    };

int find_k_number1(int k, int divide) {
    int num = 0, delta = 0, d = 1;
    while (k) {
        delta = (k-1) / divide;
        k = (k - 1) - delta * divide;
        num = num * 10 + d + delta;
        d = 0;
        divide /= 10;
    }
    return num;
}

#define _FILE_OUTPUT

#ifdef _FILE_OUTPUT
#include <fstream>
#endif

int main(void) {
    Solution sol;
    #ifdef _FILE_OUTPUT
    std::ofstream stream {"tmp.txt"};
    #endif
    auto result = sol.lexicalOrder(1253);
    for (int i = 0; i < result.size(); ++i) {
        #ifdef _FILE_OUTPUT
        stream << i+1 << "\t:\t" << result[i] << std::endl;
        #else
        std::cout << i+1 << "\t:\t" << result[i] << std::endl;
        #endif
    }
    int k = 3, divide = 1111;
    #ifdef _FILE_OUTPUT
    stream << std::endl << k << " : " << find_k_number1(k, divide) << std::endl;
    #else
    std::cout << std::endl << k << " : " << find_k_number(101, 1111) << std::endl;
    #endif
    return 0;
}