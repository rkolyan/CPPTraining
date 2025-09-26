#include <type_traits>
#include <limits>
#include <vector>

//SUCCESS

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
        int maxDiff(int num) {
            /*
            a = b1,b2,b3,b4, a != 0, в случаем максимума оставляем всё как было, в случае минимума.
            в случае минимума, нужно проверить все ли числа одинаковые
            Если все числа одинаковые заменить их на 1 (на 0 нельзя)
            Иначе изменяем на 0 цифру, которая стоит первой
            Плюс надо проверять число на наличие 0
            Например число 90909 обращается в 0, то есть для того, чтобы d = 1, нужно проверять что в числе есть только цифры двух типов, один из которых 0
            Я тупой, там не должно быть лидирующих нулей
            Ну допустим, тогда если первое число 1, то берём digit_min следующее первое ненулевое, (иначе берём 0 и 0 меняем на 0)
            */
            std::vector<int> digits;
            int max_num = 0, min_num = 0, new_digit_num;
            int digit_max = 0, digit_min = 0;
            digits.reserve(max_digits<int>());
            do {
                digits.push_back(num % 10);
                num /= 10;
            } while (num);
            /*
            digit_min = digits.back();
            new_digit_num = 1;
            for (const auto &digit : digits) {
                if (digit) {
                    if (digit_min && digit != digit_min) {
                        new_digit_num = 0;
                        break;
                    } else if (!digit_min) {
                        digit_min = digit;
                    }
                }
            }
            */
            if (digits.back() == 1) {
                new_digit_num = 0;
                digit_min = 0;
                for (int i = 1; i < digits.size(); ++i) {
                    if (digits[i] != 1 && digits[i] != 0) {
                        digit_min = digits[i];
                    }
                }
            } else {
                new_digit_num = 1;
                digit_min = digits.back();
            }
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
                    min_num = min_num * 10 + new_digit_num;
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

#include <iostream>

int main(void) {
    Solution sol;
    //std::cout << sol.minMaxDifference(11981) << std::endl;
    //std::cout << sol.minMaxDifference(90) << std::endl;
    //std::cout << sol.minMaxDifference(7) << std::endl;
    std::cout << sol.maxDiff(555) << std::endl;
    std::cout << sol.maxDiff(9) << std::endl;
    std::cout << sol.maxDiff(123456) << std::endl;
    return 0;
}