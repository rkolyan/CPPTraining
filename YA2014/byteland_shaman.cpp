////Created by rkolyan on 17.01.2025.

#include <string>
#include <iostream>
#include <iterator>
#include <regex>
#include <list>

//1)Наивная реализация арифметики длинных чисел
class BigNum {
    BigNum() {
        _nums.push_back(0);
        _negative = false;
    }
    BigNum(unsigned int num) {
        _nums.push_back(num);
        _negative = false;
    }
    BigNum(int num) {
        if (num >= 0) {
            _nums.push_back(static_cast<unsigned int>(num));
            _negative = false;
        } else {
            _nums.push_back(static_cast<unsigned int>(-num));
            _negative = true;
        }
    }
    BigNum(const std::string &str) {
        //TODO: Вот здесь самое сложное, нужно научиться переводить 10-е в 256
        //TODO: Для этого нужно написать отдельную библиотеку DecimalNum
    }
    bool operator<(const BigNum &other) {
        if (_negative) {
            if (!other._negative) {
                return true;
            } else {
                if (_nums.size() < other._nums.size()) {
                    return false;
                } else if (_nums.size() > other._nums.size()) {
                    return true;
                } else {
                    for (auto iter_left = _nums.crbegin(), iter_right = _nums.crbegin(); iter_left != _nums.crend(); ++iter_left, ++iter_right) {
                        if (*iter_left > *iter_right) {
                            return true;
                        }
                        if (*iter_left < *iter_right) {
                            return false;
                        }
                    }
                }
            }
        } else {
            if (other._negative) {
                return false;
            } else {
                if (_nums.size() < other._nums.size()) {
                    return true;
                } else if (_nums.size() > other._nums.size()) {
                    return false;
                } else {
                    for (auto iter_left = _nums.crbegin(), iter_right = _nums.crbegin(); iter_left != _nums.crend(); ++iter_left, ++iter_right) {
                        if (*iter_left > *iter_right) {
                            return false;
                        }
                        if (*iter_left < *iter_right) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    bool operator<=(const BigNum &other) {
        if (_negative) {
            if (!other._negative) {
                return true;
            } else {
                if (_nums.size() < other._nums.size()) {
                    return false;
                } else if (_nums.size() > other._nums.size()) {
                    return true;
                } else {
                    for (auto iter_left = _nums.crbegin(), iter_right = _nums.crbegin(); iter_left != _nums.crend(); ++iter_left, ++iter_right) {
                        if (*iter_left > *iter_right) {
                            return true;
                        }
                        if (*iter_left < *iter_right) {
                            return false;
                        }
                    }
                }
            }
        } else {
            if (other._negative) {
                return false;
            } else {
                if (_nums.size() < other._nums.size()) {
                    return true;
                } else if (_nums.size() > other._nums.size()) {
                    return false;
                } else {
                    for (auto iter_left = _nums.crbegin(), iter_right = _nums.crbegin(); iter_left != _nums.crend(); ++iter_left, ++iter_right) {
                        if (*iter_left > *iter_right) {
                            return false;
                        }
                        if (*iter_left < *iter_right) {
                            return true;
                        }
                    }
                }
            }
        }
        return true;
    }
    bool operator==(const BigNum &other) {
        if (_negative == other._negative) {
            if (_nums.size() == other._nums.size()) {
                for (auto iter_left = _nums.crbegin(), iter_right = _nums.crbegin(); iter_left != _nums.crend(); ++iter_left, ++iter_right) { 
                    if (*iter_left != *iter_right)
                        return false;
                }
                return true;
            }
        }
        return false;
    }
    //TODO: Реализзовать несколько версий арифметических сумм, рахностей и тд и сравнить по скорости выполнения
    BigNum operator+(const BigNum &other) {
        auto result = BigNum(*this);
        if (result._negative == other._negative) {
            if (other._nums.size() > result._nums.size()) {
                result._nums.resize(other._nums.size(), 0);
            }
            result._addAnother(other._nums); 
        } else {
            if (result._negative) {
                //Значит второе число позитивное
                
            }
        }
    }
    BigNum operator-(const BigNum &other) {
        if (other._nums.size() > _nums.size()) {
            _nums.resize(other._nums.size(), 0);
        }
    }
private:
    void _addAnother(const std::list<unsigned int> &nums) {

    }    
    std::list<unsigned int> _nums;
    bool _negative;
}

int main(void) {
    std::string A, B, S, K;
    std::size_t A_count, B_count;

    std::getline(std::cin, A);
    std::getline(std::cin, B);
    std::getline(std::cin, S);
    std::getline(std::cin, K);

    std::regex S_regex{S};
    auto start = std::sregex_iterator(A.begin(), A.end(), S_regex);
    auto stop = std::sregex_iterator();
    A_count = std::distance(start, stop);
    start = std::move(std::sregex_iterator(B.begin(), B.end(), S_regex));
    B_count = std::distance(start, stop);


    /*
    1)TODO: Выясняем длину K - от 1 до 3000 символов
    1 1 2 3  5  8  13  21 34 55
    2 4 8 16 32 64 128 256
    2)Далее
    */
    
    return 0;
}