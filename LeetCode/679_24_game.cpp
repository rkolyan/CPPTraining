#include <vector>

/*
Дан набор чисел
Нужно определить, можно ли из этих чисел построить арифметическое выражение, равное 24, используя бинарные операции и скобки
Особенности - деление вещественное, конкатенация чисел запрещениа, унарные операторы запрещены
Количество чисел == 4, ну, можно обойтись и без бектркинга...

Боже, м-да....

Случайные мысли
1)Итак, если у нас деление является вещественным, значит мы не можем хранить результаты бинарных операций как числа.
2)Также, мы же знаем результат, возможно стоит посмотреть на задачу иначе - а можно ли производить с 24 такие операции с числами из массива cards,
что после всех этих операций в результате получится 0?

По сути это ж опять задача на бектрекинг

Опишем эту задачу, как задачу CSP:
Переменные:
X = (x_1,x_2,...,x_n), x_i - число, которое используется в бинарной операции c i-мы промежуточным результатом
O = (o_1,o_2,...,o_n), o_i - бинарная операция
B = (b_1,b_2,...,b_n), b_i - скобка (означает, что следующие несколько операций будут проводится относительно 0)

Мы ищем последовательность типа S = ((o_1,b_1,x_1), ..., (o_n,b_n,x_n))
//TODO: Наличие скобок всё усложняет (ведь мы же не знаем где скобка заканчивается)
//TODO: Тогда вместо скобок можно сохранять сколько переменных будут вложены, если = 1, то вложено только 1 число
//TODO: В случае вложенности придётся решать другую задачу бектрекинга
//TODO: Нам же ещё нужно определять порядок следования чисел
Проблема - скобки, мы же можем пропустить выражения типа 24 = 23 + (1/3) + (2/3) или 21 + (26 + 10)/(4*3)
Нам нужно определить такую последоватльно
Домены:
D_X = cards, 1 <= cards[i] <= 9
D_O = {'+','-','*','/'}
D_B = {'(',')',''}, ''-отсутствие скобки, то есть нет подвыражения, '(' - операция проводится над вложенным результатом, ')'-последняя операция во вложенности
Ограничения:
C1)all_different(x_i), для каждого набора X, для i != j, x_j не может занимать D_Xi
C2)24 (o_1,b_1,x_1) (o_2,b_2,x_2),...,(o_n,b_n,x_n) == 0
Ещё ограничения:
C3)Пусть Lb_i - количество незакрытых скобок слева от и в i-й позиции (или, другими слова, текущий уровень вложенности),
Rb_i - количество закрытых скобок справа от i-й позиции. Тогда для любого i от 1 до n должно выполняться Lb_i = Rb_i
C4)Увы, из-за присутствия деления и разности, мы не можем зафиксировать значение за какой-то конкретной x_i, обе операции не коммутативны и не ассоциативны


Итак, тут как будто комплексный бектрекинг (бектрекинг с подбектрекингами)

Наверное можно и без бектрекинга, при помощи динамического программирования, только в качестве состояния у нас будет дробь, тогда:
1)При делении на число, домножаем её знаменатель на него
2)При умножении на число, домножаем числитель на число
3)При складывании/вычитании/умножении/делении дробей получаем новую дробь как в обычной арифметике
4)В случае умножения и деления желательно сокращать дроби, если это возможно, хотя возможно это будет бессмысленно при условиях задачи

Итак, dp[bit] - список дробей, полученных через арифметические выражения cо списком дробей из dp[bit - 2^k] и k-м числом из массива cards, где bit & (2^k) != 0
bit - определяет какие числа участвуют выражении
bit = 0000 - пустое выражение
bit & 0001 -участвует первое число
bit & 0010 - второе
и тд...


*/

//SUCCESS, 3 ms, побеждает 90.31 %, мое решение без потери точности и наверное медленее из-за всяких замедлений в памяти
/*
Решение за 0 ms, с возможной потерей точности
class Solution {
public:
    bool valid(double a,double b){
        return fabs(a+b-24.0)<0.0001 | fabs(a-b-24.0)<0.0001 | fabs(a*b-24.0)<0.0001 | (b!=0 and fabs(a/b-24.0)<0.0001);
    }
    bool valid(double a,double b,double c){
        return valid(a+b,c) |valid(a,b+c) |valid(a-b,c)|valid(a,b-c)|valid(a*b,c)|valid(a,b*c)|valid(a/b,c)|valid(a,b/c);
    }
    bool get_perumutation(int idx,vector<double>& card){
        if(idx==4){
           return valid(card[0]+card[1],card[2],card[3]) |
                    valid(card[0],card[1]+card[2],card[3]) |
                    valid(card[0],card[1],card[2]+card[3]) |
                    valid(card[0]-card[1],card[2],card[3]) |
                    valid(card[0],card[1]-card[2],card[3]) |
                    valid(card[0],card[1],card[2]-card[3]) |
                    valid(card[0]*card[1],card[2],card[3]) |
                    valid(card[0],card[1]*card[2],card[3]) |
                    valid(card[0],card[1],card[2]*card[3]) |
                    valid(card[0]/card[1],card[2],card[3]) |
                    valid(card[0],card[1]/card[2],card[3]) |
                    valid(card[0],card[1],card[2]/card[3]);

        }
        int res=false;
        unordered_set<int> s;
        for(int i=idx;i<4 and !res;i++){
            if(s.count(card[i]))
                continue;
            s.insert(card[i]);
            swap(card[i],card[idx]);
            res|=get_perumutation(idx+1,card);
            swap(card[i],card[idx]);
        }
        return res;
    }
    bool judgePoint24(vector<int>& cards) {
        vector<double> card;
        int n=cards.size();
        for(int i=0;i<n;i++){
            card.push_back((double)cards[i]);
        }
        return get_perumutation(0,card);
    }
};
*/

class Solution {
private:
    class Fraction {
    private:
        int numerator, denominator;
    public:
        Fraction(int num) {
            numerator = num;
            denominator = 1;
        }
        Fraction(const Fraction &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        Fraction &operator*=(const Fraction &other) {
            numerator *= other.numerator;
            denominator *= other.denominator;
            return *this;
        }
        Fraction &operator/=(const Fraction &other) {
            numerator *= other.denominator;
            denominator *= other.numerator;
            return *this;
        }
        Fraction &operator-=(const Fraction &other) {
            numerator *= other.denominator;
            int diff = other.numerator * denominator;
            numerator -= diff;
            denominator *= other.denominator;
            return *this;
        }
        Fraction &operator+=(const Fraction &other) {
            numerator *= other.denominator;
            int diff = other.numerator * denominator;
            numerator += diff;
            denominator *= other.denominator;
            return *this;
        }
        Fraction operator*(const Fraction &other) const {
            Fraction result(*this);
            result *= other;
            return result;
        }
        Fraction operator/(const Fraction &other) const {
            Fraction result(*this);
            result /= other;
            return result;
        }
        Fraction operator+(const Fraction &other) const {
            Fraction result(*this);
            result += other;
            return result;
        }
        Fraction operator-(const Fraction &other) const {
            Fraction result(*this);
            result -= other;
            return result;
        }
        bool isEqual(int num) {
            if (denominator) {
                int tmp_res = numerator / denominator;
                if (tmp_res * denominator == numerator && tmp_res == num)
                    return true;
            }
            return false;
        }
    };
    bool isBinaryEqualNum(const std::vector<Fraction> &fractions1, const std::vector<Fraction> &fractions2) {
        for (const auto &fraction1 : fractions1) {
            for (const auto &fraction2 : fractions2) {
                if ((fraction1 * fraction2).isEqual(24)) {
                    return true;
                }
                if ((fraction1 + fraction2).isEqual(24)) {
                    return true;
                }
                if ((fraction1 / fraction2).isEqual(24)) {
                    return true;
                }
                if ((fraction2 / fraction1).isEqual(24)) {
                    return true;
                }
                if ((fraction1 - fraction2).isEqual(24)) {
                    return true;
                }
                if ((fraction2 - fraction1).isEqual(24)) {
                    return true;
                }
            }
        }
        return false;
    }
    void addFractions(const std::vector<Fraction> &fractions1, const std::vector<Fraction> &fractions2, std::vector<Fraction> &result) {
        for (const auto &fraction1 : fractions1) {
            for (const auto &fraction2 : fractions2) {
                result.push_back(fraction1 + fraction2);
                result.push_back(fraction1 * fraction2);
                result.push_back(fraction1 / fraction2);
                result.push_back(fraction2 / fraction1);
                result.push_back(fraction1 - fraction2);
                result.push_back(fraction2 - fraction1);
            }
        }
    }
public:
    bool judgePoint24(std::vector<int>& cards) {
        std::vector<std::vector<Fraction>> dp(15);
        int index = 0, index2 = 0;

        for (auto &element : dp) {
            element.reserve(4096);
        }
        for (int bit = 1, i = 0; i < 4; ++i, bit <<= 1) {
            dp[bit].push_back(cards[i]);
        }
        for (int bit1 = 1; bit1 < 16; bit1 <<= 1) {
            for (int bit2 = bit1 << 1; bit2 < 16; bit2 <<= 1) {
                addFractions(dp[bit1], dp[bit2], dp[bit1 | bit2]);
            }
        }
        for (int bit1 = 1; bit1 < 16; bit1 <<= 1) {
            for (int bit2 = bit1 << 1; bit2 < 16; bit2 <<= 1) {
                index = bit1 | bit2;
                index2 = 0x0F - index;
                if (isBinaryEqualNum(dp[index], dp[index2])) {
                    return true;
                }
            }
        }
        for (int bit1 = 1; bit1 < 16; bit1 <<= 1) {
            for (int bit2 = bit1 << 1; bit2 < 16; bit2 <<= 1) {
                index = bit1 | bit2;
                for (int bit3 = 1; bit3 < 16; bit3 <<= 1) {
                    index2 = bit3 | index;
                    if (index2 != index) {
                        addFractions(dp[index], dp[bit3], dp[index2]);
                    }
                }
            }
        }
        for (int bit = 1; bit < 16; bit <<= 1) {
            index = 0x0F - bit;
            if (isBinaryEqualNum(dp[index], dp[bit])) {
                return true;
            }
        }
        return false;
    }
    bool testJudjePoint24() {
        Fraction frac1(3), frac2(9), frac3(7), frac4(7);
        auto tmp_frac1 = frac3 / frac4;
        if (!tmp_frac1.isEqual(1)) {
            return false;
        }
        auto tmp_frac2 = frac2 - tmp_frac1;
        if (!tmp_frac2.isEqual(8)) {
            return false;
        }
        auto tmp_frac3 = frac1 * tmp_frac2;
        if (!tmp_frac3.isEqual(24)) {
            return false;
        }
        return true;
    }
};

#include <iostream>



int main(void) {
    std::vector<int> nums1 {4,1,8,7}, nums2 {1,2,1,2}, nums3 {3,9,7,7};
    Solution sol;
    //std::cout << sol.judgePoint24(nums1) << std::endl;
    //std::cout << sol.judgePoint24(nums2) << std::endl;
    std::cout << sol.judgePoint24(nums3) << std::endl;
    std::cout << sol.testJudjePoint24() << std::endl;
    return 0;
}