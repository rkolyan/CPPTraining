#include <iostream>
#include <cmath>
/*
int main() {
    unsigned int T = 0, k = 0;
    std::cin >> T;

    for (unsigned int i = 0; i < T; i++) {
        std::cin >> k;
        if (k % 2) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}
*/
/*
bool is_prime(unsigned int num) {
    unsigned int t = static_cast<unsigned int>(sqrt(num));
    for (unsigned int r = 2; r < t; r++) {
        if ((num / r) * r == num){
            return false;
        }
    }
    return true;
}
int main() {
    unsigned int T = 0, k = 0, x = 0;
    std::cin >> T;

    for (unsigned int i = 0; i < T; i++) {
        std::cin >> x >> k;
        if (x != 1) {
            if (k != 1) {
                std::cout << "NO" << std::endl;
            } else {
                if (is_prime(x)) {
                    std::cout << "YES" << std::endl;
                } else {
                    std::cout << "NO" << std::endl;
                }
            }
        } else {
            if (k > 1) {
                unsigned int num = 0;
                for (unsigned int j = 0; j < k; j++) {
                    num *= 10;
                    num++;
                }
                if (is_prime(num)) {
                    std::cout << "YES" << std::endl;
                } else {
                    std::cout << "NO" << std::endl;
                }
            } else {
                std::cout << "NO" << std::endl;
            }
        }
    }
    return 0;
}
*/

#include <sstream>

int main() {
    unsigned int T = 0, n = 0, q = 0, x = 0, y = 0, d = 0;
    std::string str;
    std::getline(std::cin, str);
    std::istringstream(str) >> T;

    for (unsigned int i = 0; i < T; i++) {
        std::getline(std::cin, str);
        std::istringstream(str) >> n;
        std::getline(std::cin, str);
        std::istringstream(str) >> q;
        for (unsigned int j = 0; j < q; j++) {
            std::getline(std::cin, str);
            if (str[0] == '-' && str[1] == '>') {
                std::istringstream(str.substr(2)) >> x >> y;
                x--;
                y--;
                //TODO: Вычислить d
                //Итак, у нас таблица разделяется на 4 части, если у числа старший разряд 0, то она записывается в главную диагональ, если следующий 0, то в первую четверть, иначе в 4-ю,
                //Таблица размером 2^n на 2^n
                d = 0;
                for (unsigned int bit = 1 << n; bit != 0; bit >>= 1) {
                    d <<= 2;
                    if (y & bit) {
                        if (x & bit) {
                            d |= 1;
                        } else {
                            d |= 3;
                        }
                    } else {
                        if (x & bit) {
                            d |= 2;
                        } else {
                            d |= 0;
                        }
                    }
                }
                std::cout << d + 1 << std::endl;
            } else {
                std::istringstream(str.substr(2)) >> d;
                d--;
                x = 0;
                y = 0;
                //TODO: Вычислить позицию d
                for (unsigned int k = 0; k < n; k++) {
                    x <<= 1;
                    y <<= 1;
                    switch ((d >> (2 * (n - k - 1))) & 3)
                    {
                    case 3:
                        y |= 1;
                        x |= 0;
                        break;
                    case 2:
                        y |= 0;
                        x |= 1;
                        break;
                    case 1:
                        y |= 1;
                        x |= 1;
                    }
                }
                std::cout << x + 1 << ' ' << y + 1 << std::endl;
            }
        } 
    }
    return 0;
}