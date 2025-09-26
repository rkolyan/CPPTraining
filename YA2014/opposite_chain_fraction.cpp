#include <list>
#include <vector>
#include <iostream>

class BigNum {
    public:
        BigNum(unsigned int num) {
            _digits.clear();
            _digits.push_back(num);
        }
        BigNum &operator=(BigNum &&other) {
            _digits = std::move(other._digits);
            return *this;
        }
        BigNum &operator=(const BigNum &other) = default;
        BigNum &operator+=(const BigNum &other) {
            if (other._digits.size() > _digits.size()) {
                _digits.resize(other._digits.size());
            }
            auto otherIter = other._digits.cbegin();
            auto iter = _digits.begin();
            unsigned int tmp_sum = 0, remind = 0; 
            for (; otherIter != other._digits.cend(); iter++, otherIter++) {
                tmp_sum = *iter + *otherIter + remind;
                if (tmp_sum < *iter) {
                    remind = 1;
                } else {
                    remind = 0;
                }
                *iter = tmp_sum;
            }
            if (remind) {
                if (iter == _digits.end()) {
                    _digits.push_back(remind);
                } else {
                    *iter += remind;
                }
            }
            return *this;
        }
        /////////ОПАСНОСТЬ, РАБОТАЕТ ТОЛЬКО ЕСЛИ правое число меньше 
        BigNum&& operator-(const BigNum &other) {
            std::list<unsigned int> digits;
            unsigned int digit = 0, remind = 0;
            std::copy(_digits.cbegin(), _digits.cend(), digits.begin());
            auto iter = digits.begin();
            for (const auto &elem : other._digits) {
                digit = *iter - elem - remind;
                if (digit > *iter || (digit == *iter && remind))
                    remind = 1;
                *iter = digit;
                iter++;
            }
            *iter -= remind;
            BigNum result(std::move(digits));
            result._clear_zeros();
            return std::move(result);
        }
        BigNum&& operator+(const BigNum &other) {
            std::list<unsigned int> digits;
            std::copy(_digits.cbegin(), _digits.cend(), digits.begin());
            BigNum result(std::move(digits));
            result += other;
            return std::move(result);
        }
            /*
                element = текущее число
                берём count = 0
                
                берем b1 = 1 и сдвигаем её побитово влево 32 раза (b1 <<= 1)
                с другой стороны береём b2 = 0 и введём вправо делая (b1 = (b1 >> 1) | (1 << 31))
                b1 используем, для того, чтобы выяснить утсановлен ли бит в num
                Если установлен, то
                    1)правую часть сохраняем в tmp1 (tmp1 = ((~b2) & element) << (b1 - 1);
                    2)левую часть сохраняем в tmp2 (tmp2 = (b2 & element) >> (32 - b1)); //TODO: сомневаюсь насчет 32 - b1
                    3)далее, part1_new = part1 + tmp1;
                    если part1_new < part1, то part2++;
                    4)part2 += tmp2; (part2 не может переполниться, но кто знает)
                Далее после всех вычислений в part1_new = part1 + remind
                Если part1_new < par1, то part2++;
                remind = part2;
                part1 записываем в текущее число

                В конце если part2 != 0, то добавляем его последним числом
            */ 
        BigNum operator*(unsigned int num) const {
            std::list<unsigned int> digits;
            //digits.resize(_digits.size() + 1);
            //std::fill(digits.begin(), digits.end(), 0);
            unsigned int tmp1 = 0, tmp2 = 0, remind = 0, part1 = 0, part1_new = 0, part2 = 0, b1 = 1, b2 = 0;
            constexpr unsigned int bitsize = sizeof(unsigned int) * 8;
            for (const auto &elem : _digits) {
                part1 = 0;
                part2 = 0;
                b1 = 1;
                b2 = 0;
                for (unsigned int count = 0; count < bitsize; count++) {
                    if (num & b1) {
                        tmp1 = ((~b2) & elem) << count;
                        tmp2 = (b2 & elem) >> count;
                        part1_new = part1 + tmp1;
                        if (part1_new < part1)
                            part2++;
                        part1 = part1_new;
                        part2 += tmp2;
                    }
                    b1 <<= 1;
                    b2 = (b2 >> 1) | (1 << (bitsize - 1));
                }
                part1_new = part1 + remind;
                if (part1_new < part1)
                    part2++;
                part1 = part1_new;
                digits.push_back(part1);
                remind = part2;
            }
            if (remind)
                digits.push_back(remind);
            return BigNum(std::move(digits));
        }
        BigNum &operator<<=(unsigned int power) {
            for (unsigned int i = 0; i < power; i++)
                _digits.push_front(0);
            return *this;
        }
        BigNum&& operator*(const BigNum &other) const {
            BigNum tmp(0), sum(0);
            unsigned int power = 0;
            for (const auto &num : other._digits) {
                tmp = *this * num;
                tmp <<= power;
                sum += tmp;
            }
            sum._clear_zeros();           
            return std::move(sum);
        }
        bool operator<(const BigNum &other) {
            if (_digits.size() < other._digits.size())
                return true;
            if (_digits.size() > other._digits.size())
                return false;
            for (auto iter = _digits.crbegin(), otherIter = other._digits.crbegin(); iter != _digits.rend(); iter++, otherIter++) {
                if (*iter < *otherIter) {
                    return true;
                } else if (*iter > *otherIter) {
                    return false;
                }
            }
            return false;
        }
        bool operator==(const BigNum &other) {
            if (_digits.size() != other._digits.size())
                return false;
            for (auto iter = _digits.crbegin(), otherIter = other._digits.crbegin(); iter != _digits.rend(); iter++, otherIter++) {
                if (*iter != *otherIter) {
                    return false;
                }
            }
            return true;
        }
    private:
        BigNum(std::list<unsigned int> &&digits) {
            _digits = std::move(digits);
        }
        void _clear_zeros() {
            bool flag = false;
            while (!_digits.back()) {
                _digits.pop_back();
            }
            if (_digits.empty())
                _digits.push_back(0);
        }
        std::list<unsigned int> _digits;
};

//TODO: Надо повторить про lvalue, rvalue, копировании, перемещении и ошибки возврата локальных данных ((здесь по-видимому она))
//TODO: Эта параща не работает, но надо всй равно доделать
int main(void) {
    /*
    1)Вычислить дробную часть [a_0, a_1,...,a_n] (то есть без a_0) которая вычисляется следующим образом
    2)\alpha_n = 1, \beta_n = a_n;
    3)Далее вычисляем \alpha_{i-1} = \beta_i, \beta_{i-1} = a_{i-1} * \beta_i + \alpha_i
    4)Вычисляем дробь \frac{\gamma_1}{\beta_1} - это дробная часть искомого числа [b_0, b_1, ..., b_k] (опять же вычисляем часть без b_0)
    \gamma_1 = \beta_1 - \alpha_1
    5)Далее берем \phi = 0, \psi = 1
    6)Начинаем цикл
    b = 0
    Пока \frac{\psi}{b * \psi + \phi} > \frac{\gamma_1}{\beta_1} (Ну или \psi * \beta_1 > \gamma_1 * (b * \psi + \phi))
        инкрементируем b (умножение можно оптимизировать просто прибавляя к нижней части \psi)
        (Ну, или к числу \gamma_1 * (b * \psi + \phi) прибавляем \gamma_1 * \psi, а это также можно сделать константой \delta)
    Если \psi * \beta_1 = \gamma_1 * (b * \psi + \phi) выйти из цикла
    Добавляем 
    обновляем текущее b = 0
    \phi = старое \psi
    \psi = старое то выражение снизу
    7)вычисляем b_0 = - a_0

    Оптимизированная часть выглядит так
    6)Начинаем цикл:
    b = 0
    \ksi = \psi; \ksi - числитель дроби
    \eta = \phi; \eta - знаменатель дроби
    //Левую часть выражения можно сделать временой константой и не вычислять каждый раз при сравнении
    pb = \psi * beta_1;
    //Правую часть выражения тоже можно иниализировать как gp
    gp = \gamma_1 * \phi;
    //А после кажой итерации к ней прибавляется gp_delta
    gp_delta = \gamma_1 * \psi
    Пока pb > gp
        b++;
        gp += gp_delta
        eta += \psi;
    Если pb == gp
        break;
    \phi = \ksi
    \psi = \eta 
    */
    //TODO: Судя по скорости обработки там очень простая задача (на вариант с 100000 элементами должна уходить менее 1 секунды, а у меня миллиард лет выйдет)
    //TODO: Этот вариант я хз правильно ли работает, но в связи 
    //TODO: с тем, что до меня долго доходят простые алгоритмические решения, я 
    //TODO: в начале попробую дописать до конца этот, потом пораскину мозгами ещё раз
    unsigned int N = 0;
    int a0 = 0;
    std::vector<unsigned int> a_vector;
    std::cin >> N;
    std::cin >> a0;
    a_vector.resize(N);
    for (auto &elem : a_vector) {
        std::cin >> elem;
    }
    
    BigNum alpha(0), beta(1), tmp_alpha(0), tmp_beta(0);
    for (auto iter = a_vector.crbegin(); iter != a_vector.crend(); iter++) {
        tmp_beta = std::move((beta * *iter) + alpha);
        tmp_alpha = std::move(beta);
        alpha = std::move(tmp_alpha);
        beta = std::move(tmp_beta);
    }
    BigNum gamma(0);
    gamma = std::move(beta - alpha);
    BigNum phi(0), psi(1), ksi(0), eta(0), pb(0), gp(0), gp_delta(0);
    unsigned int b = 0;
    std::list<unsigned int> b_list;
    for (;;) {
        ksi = psi;
        eta = phi;
        pb = std::move(psi * beta);
        gp = std::move(gamma * phi);
        gp_delta = std::move(gamma * psi);
        b = 0;
        while (gp < pb) {
            b++;
            gp += gp_delta;
            eta += psi;
        }
        b_list.push_front(b);
        if (gp == pb)
            break;
        else//TODO: Наверное стоит ещё уменьшить eta на psi
            std::cout << b << std::endl;
        phi = ksi;
        psi = eta;
    }
    return 0;
}