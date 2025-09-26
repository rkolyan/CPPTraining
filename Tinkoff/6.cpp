#include <iostream>

/*
Как найти НОК?
a + b = n
1)Перебор?
2)Если число чётное, то n/2
3)Если число нечётное? одно из чисел по любому будет больше второго, тогда, в этом сулчае наименьшее кратное должно быть этим вторым числом, в ином случае НОК > n
Какиме числа подходят: 2x + x, 3y + y - не может быть (у нас число не чётное), 4z + z, но 2x < 3y < 4z. Таким образом делим число на 3, 5 и тд пока не найдем подходящее число
*/

int main(void) {
    unsigned int N = 0;
    std::cin >> N;
    if (N % 2) {
        auto end = N / 3;
        auto tmp = 3;
        bool prime = true;
        for (unsigned int j = 3; j <= end; j += 2) {
            tmp = N / j;
            if (tmp * j == N) {
                prime = false;
                std::cout << tmp << ' ' << N - tmp << std::endl;
                break;
            }
        }
        if (prime) {
            std::cout << 1 << ' ' << N - 1 << std::endl;
        }
    } else {
        auto a = N / 2;
        std::cout << a << ' ' << a << std::endl;
    }
    return 0;
}