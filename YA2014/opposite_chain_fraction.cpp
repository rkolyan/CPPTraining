//
// Created by rkolyan on 26.01.2025.
//

#include <vector>
#include <list>
#include <iostream>

class BigNum {
private:
    enum sign_t {
        NEGATIVE = 0,
        POSITIVE = 1
    } _sign;
    std::list<unsigned int> _digits;

    BigNum(std::list<unsigned int> &&digits, sign_t sign) {
        _digits = std::move(digits);
        _sign = sign;
    }
    std::list<unsigned int> &&_subtract(const BigNum &num1, const BigNum &num2) {
        //Требование: У первого должен быть длиннее или равен по размеру списка
        std::list<unsigned int> new_digits;
        unsigned int diff = 0, remind = 0;
        auto num1_iter = num1._digits.cbegin();
        for(auto num2_iter = num2._digits.cbegin(); num2_iter != num2._digits.cend(); num1_iter++, num2_iter++) {
            diff = *num1_iter - *num2_iter - remind;
            remind = 0;
            if (diff > *num1_iter || diff == *num1_iter && *num2_iter != 0)
                remind = 1;
            new_digits.push_back(diff);
        }
        for (; num1_iter != _digits.end(); num1_iter++) {
            diff = *num1_iter - remind;
            remind = 0;
            if (diff > *num1_iter)
                remind = 1;
            new_digits.push_back(diff);
        }
        if (remind) {
            //Перевод последнего разряда в дополнительный код
            new_digits.back() = ~(new_digits.back()) + 1;
        }
        while (!new_digits.empty() && new_digits.back() == 0)
            new_digits.pop_back();
        if (!new_digits.empty())
            new_digits.push_front(0);
        return std::move(new_digits);
    }
    std::list<unsigned int> &&_add(const BigNum &num1, const BigNum &num2) {
        //Требование аналогичное subtract
        std::list<unsigned int> new_digits;
        unsigned int sum = 0, remind = 0;
        auto num1_iter = num1._digits.cbegin();
        for(auto num2_iter = num2._digits.cbegin(); num2_iter != num2._digits.cend(); num1_iter++, num2_iter++) {
            sum = *num1_iter + *num2_iter + remind;
            remind = 0;
            if (sum < *num1_iter || sum == *num1_iter && *num2_iter != 0)
                remind = 1;
            new_digits.push_back(sum);
        }
        for (; num1_iter != _digits.end(); num1_iter++) {
            sum = *num1_iter + remind;
            remind = 0;
            if (sum < *num1_iter)
                remind = 1;
            new_digits.push_back(sum);
        }
        if (remind) {
            new_digits.push_back(1);
        }
        //Думаю в старших степенях после сложения не может быть 0-й, поэтому опустил выражения по очистке лишних нулей
        return std::move(new_digits);
    }
    static bool _less_abs(const BigNum &num1, const BigNum &num2) {
        if (num1._digits.size() == num2._digits.size()) {
            for (auto iter = num1._digits.crbegin(), other_iter = num2._digits.crbegin(); iter != num1._digits.crend(); iter++, other_iter++) {
                if (*iter >= *other_iter)
                    return false;
            }
        } else if (num1._digits.size() >= num2._digits.size()) {
            return false;
        }
        return true;
    }
public:
    BigNum(unsigned int base) {
        _digits.push_front(base);
        _sign = POSITIVE;
    }
    BigNum &operator=(BigNum &&other) noexcept {
        _digits = std::move(other._digits);
        return *this;
    }
    BigNum &operator=(const BigNum &other) {
        _digits.clear();
        std::copy(other._digits.begin(), other._digits.end(), _digits.begin());
        return *this;
    }
    BigNum &&operator+(const BigNum &other) {
        std::list<unsigned int> new_digits;
        sign_t new_sign = POSITIVE;
        if (_sign == POSITIVE) {
            if (other._sign == POSITIVE) {
                if (_digits.size() >= other._digits.size()) {
                    new_digits = std::move(_add(*this, other));
                } else {
                    new_digits = std::move(_add(other, *this));
                }
            } else {
                if (_less_abs(other, *this)) {
                    new_digits = std::move(_subtract(*this, other));
                } else {
                    new_digits = std::move(_subtract(other, *this));
                    new_sign = NEGATIVE;
                }
            }
        } else {
            if (other._sign == POSITIVE) {
                if (_less_abs(other, *this)) {
                    new_digits = std::move(_subtract(*this, other));
                    new_sign = NEGATIVE;
                } else {
                    new_digits = std::move(_subtract(other, *this));
                }
            } else {
                if (_digits.size() >= other._digits.size()) {
                    new_digits = std::move(_add(*this, other));
                } else {
                    new_digits = std::move(_add(other, *this));
                }
                new_sign = NEGATIVE;
            }
        }
        return std::move(BigNum(std::move(new_digits), new_sign));
    }
    BigNum &&operator-(const BigNum &other) {
        std::list<unsigned int> new_digits;
        sign_t new_sign = POSITIVE;
        if (_sign == POSITIVE) {
            if (other._sign == POSITIVE) {
                if (_less_abs(*this, other)) {
                    new_digits = std::move(_subtract(other, *this));
                    new_sign = NEGATIVE;
                } else {
                    new_digits = std::move(_subtract(*this, other));
                }
            } else {
                if (_digits.size() >= other._digits.size())
                    new_digits = std::move(_add(*this, other));
                else
                    new_digits = std::move(_add(other, *this));
            }
        } else {
            if (other._sign == POSITIVE) {
                if (_digits.size() >= other._digits.size())
                    new_digits = std::move(_add(*this, other));
                else
                    new_digits = std::move(_add(other, *this));
                new_sign = NEGATIVE;
            } else {//Оба числа отрицательные
                if (_less_abs(*this, other)) {
                    new_digits = std::move(_subtract(other, *this));
                } else {
                    new_digits = std::move(_subtract(*this, other));
                    new_sign = NEGATIVE;
                }
            }
        }
        return std::move(BigNum(std::move(new_digits), new_sign));
    }
    bool operator<=(const BigNum &other) const {
        if (_digits.size() == other._digits.size()) {
            for (auto iter = _digits.crbegin(), other_iter = other._digits.rbegin(); iter != _digits.rend(); iter++, other_iter++) {
                if (*iter > *other_iter)
                    return false;
            }
        } else if (_digits.size() > other._digits.size()) {
            return false;
        }
        return true;
    }
    bool operator<(const BigNum &other) const {
        if (_sign == POSITIVE) {
            if (other._sign == POSITIVE) {
                return _less_abs(*this, other);
            } else {
                return false;
            }
        } else {
            if (other._sign == POSITIVE) {
                return true;
            } else {
                return _less_abs(other, *this);
            }
        }
        return false;
    }
    bool operator==(const BigNum &other) {
        if (_digits.size() == other._digits.size()) {
            for (auto iter = _digits.crbegin(), other_iter = other._digits.rbegin(); iter != _digits.rend(); iter++, other_iter++) {
                if (*iter != *other_iter)
                    return false;
            }
        } else {
            return false;
        }
        return true;
    }
    BigNum operator*(const BigNum &other) {
        std::list<unsigned int> new_digits;
        std::vector<unsigned int> tmp_vector;
        auto digit_iter = _digits.cbegin();
        auto tmp_iter = tmp_vector.begin();
        unsigned int power = 0, tmp = 0;
        constexpr std::size_t bit_count = sizeof(unsigned int) * 8;
        sign_t new_sign = (_sign ^ other._sign) ? POSITIVE : NEGATIVE;
        new_digits.resize(_digits.size() + other._digits.size(), 0);
        tmp_vector.resize(_digits.size() + 1);
        for (const auto &elem : other._digits) {
            tmp = 0;
            digit_iter = _digits.cbegin();
            tmp_iter = tmp_vector.begin();
            for (; digit_iter != _digits.cend(); digit_iter++, tmp_iter++)
                *tmp_iter = *digit_iter;
            *tmp_iter = 0;
            for (unsigned int i = 0, pos = 1; i < bit_count; i++, pos <<= 1) {
                if (pos & elem) {

                }
            }
            power++;
        }
        return BigNum(1);//TODO:
    }
    BigNum operator*(unsigned int num) {
        //TODO:
        return BigNum(1);//TODO:
    }
};


int main(void) {
    std::size_t N = 0;
    int a0 = 0;
    std::vector<unsigned int> anums;
    std::list<unsigned int> bnums;

    std::cin >> N;
    anums.resize(N);
    std::cin >> a0;
    for (std::size_t i = 0; i < N; i++) {
        std::cin >> anums[i];
    }

    BigNum alpha(0), beta(1), tmp(1);//Числа, которые при вычислении используют anums
    BigNum eta(0), ksi(1);//Числа, которые используют bnums
    //1)Вычислили alpha и beta
    for (auto a_iter = anums.crbegin(); a_iter != anums.crend(); a_iter++) {
        tmp = std::move(alpha);
        alpha = std::move(beta);
        beta = std::move(alpha * *(a_iter) + tmp);
    }
    alpha = beta - alpha;
    //1)Вычисляем
    /*
     * Алгоритм следующий
     * 1)вычисляем b0 - это число скорее всего = 1 - a0 - 1
     * 2)Далее, мы вычисляем
     */
}