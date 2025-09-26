#include <type_traits>
#include <limits>
#include <cmath>
#include <vector>
#include <iostream>



template <typename T>
constexpr size_t max_digits() {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    
    constexpr T max_value = std::numeric_limits<T>::max();
    size_t digits = 0;
    T n = max_value;
    do {
        n /= 10;
        ++digits;
    } while (n != 0);
    
    return digits;
}

class Solution {
    public:
        int minMaxDifference(int num) {
            /*
            Итак, логично, что нужно разложить число и превращать только последнюю цифру
            */
            std::vector<int> digits;
            int max_num = 0, min_num = 0;
            int digit_max = 0, digit_min = 0;
            digits.reserve(max_digits<int>());
            do {
                digits.push_back(num % 10);
                num /= 10;
            } while (num);
            digit_min = digits.back();
            digit_max = digits.back();
            if (digits.back() == 9) {
                for (auto digit_iter = digits.crbegin(); digit_iter != digits.crend();++digit_iter) {
                    if (*digit_iter != 9) {
                        digit_max = *digit_iter;
                        break;
                    }
                }
            }
            for (auto digit_iter = digits.crbegin(); digit_iter != digits.crend();++digit_iter) {
                if (*digit_iter == digit_min) {
                    min_num *= 10;
                } else {
                    min_num = min_num * 10 + *digit_iter;
                }
                if (*digit_iter == digit_max) {
                    max_num = max_num * 10 + 9;
                } else {
                    max_num = max_num * 10 + *digit_iter;
                }
            }
            return max_num - min_num;
        }
};

int main(void) {
    Solution sol;
    std::cout << sol.minMaxDifference(11981) << std::endl;
    std::cout << sol.minMaxDifference(90) << std::endl;
    std::cout << sol.minMaxDifference(7) << std::endl;
    std::cout << sol.minMaxDifference(0) << std::endl;
    return 0;
}