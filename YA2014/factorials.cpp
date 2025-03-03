//
// Created by rkolyan on 11.09.2024.
//

#include <iostream>
#include <vector>

//SUCCESS

class BigNum {
public:
    BigNum(std::size_t size) {
        _nums_vector.resize(size);
        _tmp_vector.resize(size);
        _accum_vector.resize(size);
        std::fill(_nums_vector.begin(), _nums_vector.end(), 0);
        _is_overflow = false;
    }
    void clear() {
        std::fill(_nums_vector.begin(), _nums_vector.end(), 0);
    }
    BigNum &operator++() {
        unsigned char num = 1;
        std::size_t index = 0;
        while (num != 0 && index < _nums_vector.size()) {
            num += _nums_vector[index];
            _nums_vector[index] = num % 10;
            num /= 10;
            index++;
        }
        if (index == _nums_vector.size())
            _is_overflow = true;
        return *this;
    }
    BigNum &operator *=(unsigned int num) {
        unsigned tmp = 0, mult = 0, remind = 0, zeros = 0, sum = 0;
        std::fill(_accum_vector.begin(), _accum_vector.end(), 0);
        while (num) {
            tmp = num % 10;
            if (tmp) {
                //1)Копируем большое число в буфер
                remind = 0;
                std::fill(_tmp_vector.begin(), _tmp_vector.end(), 0);
                for (auto tmp_digit_iter = _tmp_vector.begin(), nums_digit_iter = _nums_vector.begin(); nums_digit_iter != _nums_vector.end(); tmp_digit_iter++, nums_digit_iter++) {
                    mult = (*nums_digit_iter) * tmp + remind;
                    *tmp_digit_iter = mult % 10;
                    remind = mult / 10;
                }
                remind = 0;
                for (auto accum_digit_iter = std::next(_accum_vector.begin(), zeros), tmp_digit_iter = _tmp_vector.begin(); accum_digit_iter != _accum_vector.end(); accum_digit_iter++, tmp_digit_iter++) {
                    sum = *accum_digit_iter + *tmp_digit_iter + remind;
                    *accum_digit_iter = sum % 10;
                    remind = sum / 10;
                }
            }
            num /= 10;
            zeros++;
        }
        for (auto accum_digit_iter = _accum_vector.begin(), nums_digit_iter = _nums_vector.begin(); accum_digit_iter != _accum_vector.end(); accum_digit_iter++, nums_digit_iter++)
            *nums_digit_iter = *accum_digit_iter;
        return *this;
    }
    void print() {
        auto iter = _nums_vector.end();
        char sym[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        do {
            iter--;
            std::cout << sym[static_cast<int>(*iter)];
        } while (iter != _nums_vector.begin());
        std::cout << std::endl;
    }
    unsigned int get_last_nonzero() {
        for (unsigned char & digit : _nums_vector) {
            if (digit) {
                return static_cast<unsigned int>(digit);
            }
        }
        return 0;
    }
private:
    std::vector<unsigned char> _nums_vector;
    std::vector<unsigned char> _tmp_vector;
    std::vector<unsigned char> _accum_vector;
    bool _is_overflow;
};

void calculate_sums(BigNum &bnum, unsigned int n, unsigned int k) {
    unsigned int num = 1;
    ++bnum;
    for (unsigned int i = n; i > 0; i--) {
        num = 1;
        for (unsigned int j = 0; j < k; j++) {
            num *= i;
        }
        bnum *= num;
        ++bnum;
    }
}

unsigned int find_last_nonzero_early(unsigned int n, unsigned int k) {
    unsigned int num = 1, num2 = 1, sum = 0;
    for (unsigned int i = 0; i <= n; i++) {
        num = 1;
        for (unsigned int tmp = 1; tmp <= i; tmp++) {
            num2 = 1;
            for (unsigned j = 0; j < k; j++) {
                num2 *= tmp;
            }
            num *= num2;
        }
        sum += num % 100000000;
    }
    while (sum % 10 == 0) {
        sum /= 10;
    }
    return sum % 10;
}

unsigned calculate_simple(unsigned int n, unsigned int k) {
    unsigned int num = 1, num2 = 1, sum = 0;
    for (unsigned int n1 = 0; n1 <= n; n1++) {
        num = 1;
        for (unsigned int n2 = 1; n2 <= n1; n2++) {
            num *= n2;
        }
        num2 = 1;
        for (unsigned j = 0; j < k; j++)
            num2 *= num;
        sum += num2;
    }
    return sum;
}

/*
int main(int argc, char **argv) {
    unsigned int n = 100, k = 3, res1 = 0, res2 = 0;
    //std::cin >> n >> k;
    BigNum bnum(200);
    for (unsigned int n1 = 0; n1 <= n; n1++) {
        for (unsigned int k1 = 1; k1 <= k; k1++) {
            calculate_sums(bnum, n1, k1);
            res1 = bnum.get_last_nonzero();
            res2 = find_last_nonzero_early(n1, k1);
            if (res1 != res2) {
                std::cout << n1 << " " << k1 <<"\nErr:\n";
                bnum.print();
                std::cout << res1 << " " << res2 << std::endl;
            }
            bnum.clear();
        }
    }
    return 0;
}
*/
int main(int argc, char **argv) {
    unsigned int n = 100, k = 3, res1 = 0, res2 = 0;
    std::cin >> n >> k;
    BigNum bnum(200);
    calculate_sums(bnum, n, k);
    std::cout << bnum.get_last_nonzero();
    return 0;
}