#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <climits>


//TODO:Не решил, как и 3170

class Solution {
    private:
        #define SYMS_COUNT '4'-'0' + 1
        #define FIRST_SYMBOL '0'
    public:
        int maxDifference(std::string s, int k) {
            auto my_less = [](const std::pair<std::string::value_type, int> &a, const std::pair<std::string::value_type, int> &b) {
                return a.second < b.second;
            };
            auto my_greater = [](const std::pair<std::string::value_type, int> &a, const std::pair<std::string::value_type, int> &b) {
                return a.second > b.second;
            };
            std::map<std::string::value_type, int> odd_max_queue_begin, odd_max_queue, even_min_queue_begin, even_min_queue;
            std::set<std::pair<int, std::string::value_type>> odd_counts_begin, odd_counts, even_counts_begin, even_counts;
            std::array<int, SYMS_COUNT> arr;
            int diff = INT_MIN;
            int tmp_count = 0;
            std::string::value_type tmp_sym = 0;
            const auto n = s.size();
            for (int i = 0; i < k; ++i) {
                arr[s[i] - FIRST_SYMBOL]++;
            }
            for (int i = 0; i < SYMS_COUNT; ++i) {
                if (arr[i] % 2) {
                    odd_max_queue_begin.emplace(i + FIRST_SYMBOL, arr[i]);
                    odd_counts_begin.emplace(arr[i], i + FIRST_SYMBOL);
                } else {
                    even_min_queue_begin.emplace(i + FIRST_SYMBOL, arr[i]);
                    even_counts_begin.emplace(arr[i], i + FIRST_SYMBOL);
                }
            }
            for (int t = 0; t < n - k; ++t) {
                if (!odd_counts_begin.empty() && !even_counts_begin.empty()) {
                    const auto odd_max = (*odd_counts_begin.rbegin()).first;
                    const auto even_min = (*even_counts_begin.begin()).first;
                    diff = std::max(odd_max - even_min, diff);
                }
                odd_max_queue = odd_max_queue_begin;
                even_min_queue = even_min_queue_begin;
                odd_counts = odd_counts_begin;
                even_counts = even_counts_begin;
                auto odd_iter = odd_max_queue.begin();
                auto even_iter = even_min_queue.begin();
                for (int i = 0; i < n - k - t; ++i) {
                    tmp_sym = s[i];
                    odd_iter = odd_max_queue.find(tmp_sym);
                    if (odd_iter != odd_max_queue.end()) {
                        tmp_count = (*odd_iter).second;
                        odd_max_queue.erase(odd_iter);
                        odd_counts.erase(odd_counts.find(std::make_pair(tmp_count, tmp_sym)));
                        tmp_count--;
                        if (tmp_count) {
                            even_min_queue.emplace(tmp_sym, tmp_count);
                            even_counts.emplace(tmp_count, tmp_sym);
                        }
                    } else {
                        even_iter = even_min_queue.find(tmp_sym);
                        if (even_iter != even_min_queue.end()) {
                            tmp_count = (*even_iter).second;
                            even_min_queue.erase(even_iter);
                            even_counts.erase(even_counts.find(std::make_pair(tmp_count, tmp_sym)));
                            tmp_count--;
                            if (tmp_count) {
                                odd_max_queue.emplace(tmp_sym, tmp_count);
                                odd_counts.emplace(tmp_count, tmp_sym);
                            }
                        }
                        //TODO: По идее иначе быть не должно
                    }
                    tmp_sym = s[i+k+t];
                    odd_iter = odd_max_queue.find(tmp_sym);
                    if (odd_iter != odd_max_queue.end()) {
                        tmp_count = (*odd_iter).second;
                        odd_max_queue.erase(odd_iter);
                        odd_counts.erase(odd_counts.find(std::make_pair(tmp_count, tmp_sym)));
                        tmp_count++;
                        even_min_queue.emplace(tmp_sym, tmp_count);
                        even_counts.emplace(tmp_count, tmp_sym);
                    } else {
                        even_iter = even_min_queue.find(tmp_sym);
                        if (even_iter != even_min_queue.end()) {
                            tmp_count = (*even_iter).second;
                            even_min_queue.erase(even_iter);
                            even_counts.erase(even_counts.find(std::make_pair(tmp_count, tmp_sym)));
                            tmp_count++;
                            odd_max_queue.emplace(tmp_sym, tmp_count);
                            odd_counts.emplace(tmp_count, tmp_sym);
                        } else {
                            odd_max_queue.emplace(tmp_sym, 1);
                            odd_counts.emplace(1, tmp_sym);
                        }
                    }
                    if (!odd_counts.empty() && !even_counts.empty()) {
                        const auto odd_max = (*odd_counts.rbegin()).first;
                        const auto even_min = (*even_counts.begin()).first;
                        diff = std::max(odd_max - even_min, diff);
                    }
                }
                //TODO: Увеличить начальные отрезки
            }
            return diff;
            /*
            Итак, дана строка s и размер k, нужно найти максимальную разницу между нечетной и четной частотами символов в какой-нибудь подстроке subs в s,
            размер subs >= k

            Самый примитивный вариант построить dp[2][n-k+1]['z'-'a'+1], заполнить первый слой разницами для первых 
            Алгоритм следующий
            1)Составляем 2 массива с очередями приоритетов (для нечётных и чётных чисел), хранящие пары <количество символов, символ>
            2)Далее, используя временный массив частот считаем количество для каждого подотрезка со смещением i относительно начала массива и размером k элементов,
            Далее, результаты записываем в 2 очереди приоритетов dp[i], как только закончили вычислять, берём из одной очереди самое старшее значение, из другой самое младшее, вычитаем разность и сравниваем с текущим
            3)Далее, на каждой итерации t = 0 до n - k - 1 <вычисли> для каждой i = 0; i < n - k - t:
                берётся dp[i]-я очередь из неё извлекается,если в ней есть, s[i+k+t] элемент, прибавляется к количеству 1, затем отправляется в другую очередь
                в качестве очереди можно использовать flat_set, где поиск идёт по ключу = s[element], а сравнение по count[element]
                Потом делаем разность counts последних элементов и сравниваем с максимальной разностью, если хоть одна из очередей пуста, то пропускаем
            */
            /*
            Итак, у нас есть строка a1,a2,a3,...,an
            Допустим мы мы взяли первые k элементов
            
            Что могут проверять префиксы - количество каких элементов меняется на четное и нечётное
            Изучаем переход с четного на нечётное состояние
            Тогда наверное можно построить граф
            допустим есть строка 
            0432304212334213421432212
            0:0->5
            1:8->14->18->23
            2:3->7->9->13->17->21->22->24
            3:2->4->10->11->15->20
            4:1->6->12->16->19
            Итак, самое большое чётное количество элементов точно в отрезке [3, 24] - это 2 (8 штук)
            минимальное нечётное количество - 0 (1 штука), плохой пример

            Итак, тут задача вроде на sliding window и prefix sum
            итак, в подсказках сказано, что нужно сохранять два символа и 2 указателя
            0         0
              4         4      
                3   3
                  2       2   2
                            1
            
            Итак, нам нужно найти максимальную разницу между четным количеством и нечетным в подстроке
            Если мы добавим символ справа, то у нас либо какое-то чётное количество превратится в нечётное, либо 
            В качестве префиксов можно построить массив индексов следующего элемента
            */
        }
    };

#include <iostream>
int main(void) {
    Solution sol;
    std::cout << sol.maxDifference("12233", 4) << std::endl;
    std::cout << sol.maxDifference("1122211", 3) << std::endl;
    std::cout << sol.maxDifference("110", 3) << std::endl;
    return 0;
}