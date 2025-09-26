#include <vector>
#include <bitset>

//#define _TEST

#ifdef _TEST
#include <cassert>
#endif

class Solution {
#ifdef _TEST
public:
#else
private:
#endif
    #define LCM_SIZE 100001
    #define MAX_PRIME_COUNT 20
    void fill_LCM(int primes[LCM_SIZE], int complicated[LCM_SIZE]) {
        std::vector<int> stack;
        int num = 0, count = LCM_SIZE - 2;
        primes[0] = primes[1] = 0;
        stack.reserve(1000);
        for (int i = 2; i < LCM_SIZE && count > 0; ++i) {
            if (primes[i] == 0) {
                primes[i] = i;
                complicated[i] = 1;
                --count;
                stack.push_back(i);
            }
            for (const auto &prime : stack) {
                num = i * prime;
                if (num >= LCM_SIZE) {
                    break;
                }
                if (!primes[num]) {
                    primes[num] = prime;
                    complicated[num] = i;
                    --count;
                }
            }
        }
    }
    bool is_coprime(int primes[LCM_SIZE], int complicated[LCM_SIZE], char all_counts[LCM_SIZE], char found_counts[LCM_SIZE], std::vector<int> &found_primes, int num) {
        bool nocoprime = false;
        int prime;
        while (num != 1) {
            prime = primes[num];
            if (all_counts[prime]) {
                nocoprime = true;
            }
            if (!found_counts[prime]) {
                found_primes.push_back(prime);
            }
            ++found_counts[prime];
            num = complicated[num];
        }
        return nocoprime;
    }
    void add_found_counts(char all_counts[LCM_SIZE], char found_counts[LCM_SIZE], std::vector<int> &all_primes, std::vector<int> &found_primes) {
        for (const auto &prime : found_primes) {
            if (!all_counts[prime])
                all_primes.push_back(prime);
        }
        for (const auto &prime : all_primes) {
            all_counts[prime] = std::max(all_counts[prime], found_counts[prime]);
        }
        found_primes.clear();
        for (const auto &prime : all_primes) {
            found_primes.push_back(prime);
        }
    }
    void set_found_counts(char all_counts[LCM_SIZE], char found_counts[LCM_SIZE], std::vector<int> &all_primes, std::vector<int> &found_primes) {
        for (const auto &prime : all_primes) {
            all_counts[prime] = 0;
        }
        for (const auto &prime : found_primes) {
            all_counts[prime] = found_counts[prime];
        }
        all_primes.clear();
        for (const auto &prime : found_primes) {
            all_primes.push_back(prime);
        }
    }
    void clear_found_counts(char found_counts[LCM_SIZE], std::vector<int> &found_primes) {
        for (const auto &prime : found_primes) {
            found_counts[prime] = 0;
        }
        found_primes.clear();
    }
    int find_LCM(char all_counts[LCM_SIZE], const std::vector<int> &primes_stack) {
        int result = 1;
        for (const auto &prime : primes_stack) {
            for (int i = 0; i < all_counts[prime]; ++i) {
                result *= prime;
            }
        }
        return result;
    }
public:
    //Я не учел всех условий, там нужно по массиву получается ещё раз пройти пока общих множителей не будет
    std::vector<int> replaceNonCoprimes(std::vector<int>& nums) {
        int primes[LCM_SIZE] = {0}, complicated[LCM_SIZE] = {0};
        char all_counts[LCM_SIZE] = {0}, found_counts[LCM_SIZE] = {0};
        std::vector<int> all_primes, found_primes, result;
        all_primes.reserve(MAX_PRIME_COUNT);
        found_primes.reserve(MAX_PRIME_COUNT);
        result.reserve(LCM_SIZE);
        fill_LCM(primes, complicated);
        is_coprime(primes, complicated, all_counts, found_counts, found_primes, nums[0]);
        set_found_counts(all_counts, found_counts, all_primes, found_primes);
        clear_found_counts(found_counts, found_primes);
        for (int i = 1; i < nums.size(); ++i) {
            if (is_coprime(primes, complicated, all_counts, found_counts, found_primes, nums[i])) {
                add_found_counts(all_counts, found_counts, all_primes, found_primes);
            } else {
                result.push_back(find_LCM(all_counts, all_primes));
                set_found_counts(all_counts, found_counts, all_primes, found_primes);
            }
            clear_found_counts(found_counts, found_primes);
        }
        result.push_back(find_LCM(all_counts, all_primes));
        return result;
    }
};;
/*
Тут нужно написать быстрый алгоритм который брал бы каждые пары соседних чисел и в случаях если б они были взаимно просты, то заменял бы эту пару чисел на 
их наименьшее общее кратное.

Итак, всё просто, создаем структуру с 2 массивами - первый хранит составной делитель числа, второй простой и по нему без деления быстро определяем какие числа
делятся
Также создаём массив масок делителей (он нужен, чтоб определить весь интервал невзаимно простых чисел)
А также стек с записанными номерами (чтоб быстро стирать значения в маске)
Далее, начиная с первого числа проверяем делимость числа в LCM, и заполняя бит в маске, попутно проверяя он уже установлен или нет
Если все биты для текущего числа не были установлены, то это число - начало нового интервала, удаляем из стека все простые делители которые не принадлежат ему 
*/

#include <iostream>

#ifdef _TEST
bool test_LCM(Solution &sol, const std::vector<int> nums, int result) {
    int primes[10001] = {0}, complicated[10001] = {0};
    char all_counts[10001] = {0};
    std::vector<int> all_primes;
    for (const auto &num : nums) {
        if (!all_counts[num]) {
            all_primes.push_back(num);
        }
        ++all_counts[num];
    }
    sol.fill_LCM(primes, complicated);
    return sol.find_LCM(all_counts, all_primes) == result;
}

void test_is_nocoprime(Solution &sol) {
    int primes[10001] = {0}, complicated[10001] = {0};
    char all_counts[10001] = {0}, found_counts[10001] = {0};
    std::vector<int> all_primes, found_primes;

    sol.fill_LCM(primes, complicated);
    bool flag = sol.is_coprime(primes, complicated, all_counts, found_counts, found_primes, 2*5*5*3);
    assert(!flag);
    assert(found_counts[2] == 1);
    assert(found_counts[3] == 1);
    assert(found_counts[5] == 2);

}

void _fill_init_num(const std::vector<int> &nums, char counts[10001], std::vector<int> &primes) {
    for (const auto &num : nums) {
        if (!counts[num]) {
            primes.push_back(num);
        }
        ++counts[num];
    }
}

bool has_equal(const std::vector<int> &nums1, const std::vector<int> &nums2) {
    for (const auto &num : nums1) {
        for (const auto &num2 : nums2) {
            if (num == num2) {
                return true;
            }
        }
    }
    return false;
}

void test_is_coprime(Solution &sol, const std::vector<int> nums1, const std::vector<int> nums2, const std::vector<int> result) {
    int primes[10001] = {0}, complicated[10001] = {0};
    sol.fill_LCM(primes, complicated);
    char all_counts[10001] = {0}, found_counts[10001] = {0}, result_counts[10001] = {0};
    std::vector<int> all_primes, found_primes, result_primes;
    _fill_init_num(nums1, all_counts, all_primes);
    _fill_init_num(nums2, found_counts, found_primes);
    _fill_init_num(result, result_counts, result_primes);
    
    int num = sol.find_LCM(found_counts, found_primes);
    sol.clear_found_counts(found_counts, found_primes);
    bool flag = sol.is_coprime(primes, complicated, all_counts, found_counts, found_primes, num);
    assert(flag == has_equal(nums1, nums2));
}

void test_set_found_counts(Solution &sol, const std::vector<int> nums1, const std::vector<int> nums2, const std::vector<int> result) {
    char all_counts[10001] = {0}, found_counts[10001] = {0}, result_counts[10001] = {0};
    std::vector<int> all_primes, found_primes, result_primes;
    _fill_init_num(nums1, all_counts, all_primes);
    _fill_init_num(nums2, found_counts, found_primes);
    _fill_init_num(result, result_counts, result_primes);
    
    sol.set_found_counts(all_counts, found_counts, all_primes, found_primes);
    for (int i = 0; i < result_primes.size(); ++i) {
        assert(all_primes[i] == result_primes[i]);
    }
    for (int i = 0; i < 10001; ++i) {
        assert(all_counts[i] == result_counts[i]);
    }
    //sol.clear_found_counts(found_counts, found_primes);
}
#endif

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<int> nums {287,41,49,287,899,23,23,20677,5,825};
#ifdef _TEST
    assert(test_LCM(sol, {2,3,3,3,5,7}, 1890));
    test_is_nocoprime(sol);
    test_is_coprime(sol, {2,3,3}, {3,5,7}, {});
    test_is_coprime(sol, {2,2}, {3,5,7}, {});
    test_set_found_counts(sol, {2, 3}, {5, 7, 11, 11}, {5, 7, 11, 11});
    std::cout << "Все тесты пройдены нормально!" << std::endl;
#endif
    sol.replaceNonCoprimes(nums);
    return 0;
}