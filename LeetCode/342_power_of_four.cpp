#include <cmath>

//SUCCESS

class Solution {
public:
    bool isPowerOfFour(int n) {
        /*
        Здесь не сработает тот прикол как с 3^x, так как число не простое 2^x * 2^x
        Тогда по идее без циклов
        1)вычислить корень числа
        2)проверить является ли этот корень степенью двойки

        11000010000
        00111101111
        00111110000
        11000001111

        00010000
        11101111 ~
        11110000 +1
        00001111 ~
        00010000 +1

        00010100
        11101011
        11101100

        Тогда степень 2ки -определяется следующим образом (если (~num)+1)&num == num, то степень 2ки


        Пусть num - число
        если ~((~num)+1) == 0, то num - степень 2ки

        num = sqrt(n)
        */
        unsigned int num = static_cast<unsigned int>(std::sqrt(n));
        if (num * num != static_cast<unsigned int>(n) || (((~num)+1) & num) != num) {
            return false;
        }
        return true;
    }
};

int main(void) {
    Solution sol;
    sol.isPowerOfFour(16);
}