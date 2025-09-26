#include <iostream>
#include <vector>
#include <numeric>
#include <climits>
//TODO: Ненавижу задачи на факторизации

int find_primes_count(int number, std::vector<int> &primes_count_cache, const std::vector<int> &lpf) {
    if (number == 1) {
        return 0;
    }
    if (primes_count_cache[number] == 0) {
        int tmp = number, count = 0;
        while (tmp > 1) {
            count++;
            tmp /= lpf[tmp];
        }
        primes_count_cache[number] = count;
    }
    return primes_count_cache[number];
}

int find_gcd(int num1, int num2, std::vector<std::vector<int>> &gcd_cache) {
    if (gcd_cache[num1][num2] == 0) {
        gcd_cache[num1][num2] = std::gcd(num1, num2);
    }
    return gcd_cache[num1][num2];
}

void init_caches(std::vector<int> &primes_count_cache, std::vector<int> &lpf_cache, std::vector<std::vector<int>> &gcd_cache) {
    #define MAX_NUMBER 5000
    gcd_cache.resize(MAX_NUMBER+1, std::vector<int>(MAX_NUMBER + 1, 0));
    primes_count_cache.resize(MAX_NUMBER + 1, 0);
    lpf_cache.resize(MAX_NUMBER + 1, 0);
    for (unsigned int i = 2; i < lpf_cache.size(); ++i) {
        if (!lpf_cache[i]) {
            lpf_cache[i] = i;
            for (unsigned int j = i * i; j < lpf_cache.size(); j += i) {
                if (lpf_cache[j] == 0) {
                    lpf_cache[j] = i;
                }
            }
        }
    }
}

int find_minimum_operations(std::vector<int> &a, std::vector<int> &primes_count_cache, const std::vector<int> &lpf_cache, std::vector<std::vector<int>> &gcd_cache) {
    const auto N = a.size();
    int main_gcd = a.front();
    int operations_count = N;
    for (int i = 1; i < N; ++i) {
        main_gcd = find_gcd(main_gcd, a[i], gcd_cache);
    }
    for (int i = 0; i < N; ++i) {
        a[i] /= main_gcd;
        if (a[i] == 1) {
            --operations_count;
        }
    }
    if (operations_count != N) {
        return operations_count;
    }
    int i1 = 0, i2 = 1;
    int min_gcd = find_gcd(a[0], a[1], gcd_cache), tmp_gcd, cur_min_gcd;
    int min_prime_count = find_primes_count(min_gcd, primes_count_cache, lpf_cache), prime_count;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            tmp_gcd = find_gcd(a[i], a[j], gcd_cache);
            prime_count = find_primes_count(tmp_gcd, primes_count_cache, lpf_cache);
            if (prime_count < min_prime_count) {
                min_prime_count = prime_count;
                min_gcd = tmp_gcd;
                i1 = i;
                i2 = j;
            }
        }
    }
    std::vector<int> marks(N, false);
    marks[i1] = true;
    marks[i2] = true;
    /*
    Итак, 30 2145 1870 1326
    Тут должно быть 5 операций, у меня 6, потому что 2 операции math.gcd(2145, 1326) = 39, math.gcd(39, 1870) = 1 + 3 операции
    У меня в качестве первого min_gcd берётся gcd(30, 2145)
    a1,a2,a3,a4 - если общий gcd = 1, то тут по идее 6 операций (попарные gcd не равны 1 и не равны друг другу)

    Наверное тут все-таки нужны префиксы и 
    Наверное в начале
    Сохраняем в префикс min(gcd)

    Может быть стоит построить двудольный граф, где один тип вершины
   
    Короче, нужно найти подмножество минимального размера, такое, что gcd = 1
    Как вариант, берём и вычисляем текущий элемент gcd со всеми, тогда если gcd со всеми больше 1, то сохраняем это gcd как возможный вариант

    Так, ну допустим, эта задача как-то решается  через динамическое программирование
    Что можно сохранять в качестве dp[num1][num2] - наверное, количество общих множителей между числами i и k
    Итак, тогда такой вариант
    Итак, в начале просто проходимся по массиву и находим общий gcd, если есть число
    Тогда нам нужна очередь слева, в которой отмечаем, какие элементы образуются (или есть) и количество operation соответственно
    Алгоритм получается след
    */
    while (min_gcd > 1) {
        cur_min_gcd = min_gcd;
        min_prime_count = INT_MAX;
        ++operations_count;
        for (int i = 0; i < N; ++i) {
            if (!marks[i]) {
                tmp_gcd = find_gcd(min_gcd, a[i], gcd_cache);
                prime_count = find_primes_count(tmp_gcd, primes_count_cache, lpf_cache);
                if (prime_count < min_prime_count) {
                    min_prime_count = prime_count;;
                    cur_min_gcd = tmp_gcd;
                    i2 = i;
                }
            }
        }
        marks[i2] = true;
        min_gcd = cur_min_gcd;
    }
    return operations_count;
}

#include <fstream>

//#define _DEBUG
//#define _TEST

int main(void) {
#ifdef _TEST
    std::vector<int> a;
    a.reserve(5000);
    for (int i = 1; i < 5001; ++i) {
        a.push_back(i);
    }
    std::vector<int> lpf_cache, primes_count_cache;
    std::vector<std::vector<int>> gcd_cache;
    init_caches(primes_count_cache, lpf_cache, gcd_cache);
    std::cout << find_minimum_operations(a, primes_count_cache, lpf_cache, gcd_cache) << std::endl;
#else
    unsigned int t = 0, n = 0;
    std::vector<int> a;
    std::vector<int> lpf_cache, primes_count_cache;
    std::vector<std::vector<int>> gcd_cache;
    init_caches(primes_count_cache, lpf_cache, gcd_cache);
#ifdef _DEBUG
    std::ofstream stream {"output.txt"};
#endif
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> n;
        a.resize(n);
        for (auto &element : a) {
            std::cin >> element;
        }
#ifdef _DEBUG
        for (const auto &element : a) {
            stream << element << ' ';
        }
        stream << "\t --- " << find_minimum_operations(a, primes_count_cache, lpf_cache, gcd_cache) << std::endl;
#else
        std::cout << find_minimum_operations(a, primes_count_cache, lpf_cache, gcd_cache) << std::endl;
#endif
    }
#endif
    std::vector<std::string> tmp;
    tmp.resize(10, std::string(10, 'a'));
    return 0;
}