#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>

class Solution {
    public:
        long long minSum(std::vector<int>& nums1, std::vector<int>& nums2) {
            /*
            Итак, должны заменить нули в обоих массивах на такие позитивные числа,
            чтобы сумма была равна в обоих случаях причем нам надо найти минимальную
            сумму Итак, сумма в первом массиве = s1, количество нулей z1 Во втором -
            s2, z2 соответственно Итак, если |s1 - s2| < |z1-z2|, тогда -1 Неверно,
            пример |3 - 2| < |4 - 1| слева дополняем 4 единицы, справа 5 Если zi
            равна 0, при этом sj > si, тогда -1 Потому что мы не можем восстановить
            si до sj В иных случая воосстановить можно
    
            тогда расссмотрим следующую идею
            Пусть si > sj, zi, zj
            Тогда смотрим
            Если zj > si - sj + zi:
                Значит одно число из zi должно быть равно
                sj + zj = si + zi-1 + (sj+zj - si - zi + 1)
            Иначе:
                Значит одно число из zj должно быть большое
                si + zi = sj + zj-1 + (si + zi - sj - zj + 1)
            */
            int z1 = 0, z2 = 0, s1 = 0, s2 = 0;
            for (const auto& num : nums1) {
                s1 += num;
                if (!num)
                    ++z1;
            }
            for (const auto& num : nums2) {
                s2 += num;
                if (!num)
                    ++z2;
            }
            if (s2 > s1) {
                std::swap(s1, s2);
                std::swap(z1, z2);
            }
            if ((s1 > s2 && (!z2 || !z1 && s2 + z2 > s1)) || (s1 == s2 && (!z1 || !z2))) {
                return -1;
            }
            if (z2 > s1 - s2 + z1) {
                return s2 + z2;
            }
            return s1 + z1;
        }
        long long findScore(std::vector<int>& nums) {
            /*
            Следующая задача:
            Дан массив натуральных чисел
            Берём score = 0
            Далее берётся первый неотмеченный минимум из массива
            В score добавляется
            Отмечается этот элемент и справа и слева от него
            Процесс повторяется до тех пор пока все элементы не будут отмечены
            Тут наверное какой-то хитрый трюк используется
            */
            typedef int index_t;
            typedef int element_t;
            using coords = std::pair<element_t, index_t>;
            index_t cur_index = 0;
            element_t cur_element = 0;
            long long score = 0;
            std::vector<coords> container;
            bool marks[nums.size()] = {false};
            container.reserve(nums.size());
            std::priority_queue<coords, std::vector<coords>, std::greater<coords>> queue(std::greater<coords>(), std::move(container));
            for (index_t i = 0; i < nums.size(); ++i) {
                queue.emplace(nums[i], i);
            }
            for (; !queue.empty(); queue.pop()) {
                const auto &coord = queue.top();
                cur_element = coord.first;
                cur_index = coord.second;
                if (!marks[cur_index]) {
                    score += cur_element;
                    marks[cur_index] = true;
                    if (cur_index > 0) {
                        marks[cur_index - 1] = true;
                    }
                    if (cur_index < nums.size() - 1) {
                        marks[cur_index + 1] = true;
                    }
                }
            }
            return score;
        }

    long long countFairPairs(std::vector<int>& nums, int lower, int upper) {
        /*
        Итак, задача явно решается жадно
        И явно меньше O(n^2/2)
        Тогда нужно походу использовать либо жадный алгоритм, либо префиксы
        Нужно найти оптимальную подструктуру
        Итак раз вариант с суммой, тогда
        Надо хранить суммы
        Но lower и upper имеют огромные значения, значит не то
        Допустим мы можем аккумулировать суммы
        Тогда попробуем интерпретировать эту задачу в задачу о рюкзаке
        Допустим мы ищем 2 вещи, которые вмещаются 
        Предположения
        Можно отсортировать массив
        a1, a2, ..., an
        тогда если ai + a{i+1} честная пара,
        построить матрицу - O(n2)
        не выйдет
        Построить дерево?
        Допустим мы можем использовать префиксы и суффиксы
        Например мы можем идти слева
        и пишем 2 префикса
        
        Нет попробуем с отсортированным массивом
        Начиная с большего элемента:
        Далее можно использовать бинарный поиск для быстрого нахождения минимальных и максимальных левых индексов
        Тогда количество += разность индексов
        Тогда сложность будет O(nlgn) + сложность сортировки

        Тут короче явно прикол с префиксами
        
        Моя любимая задача на двоичный поиск
        */
        std::sort(nums.begin(), nums.end());
        unsigned int count = 0;
        for (unsigned int i = 0; i < nums.size(); ++i) {
            //1)Ищем двоичным поиском точной нижней границы (минимальное значение s[k], которое a[i] + s[k] >= lower)
            //2)Ищем двоичным поиском верхней границы (миниманльного значения s[t], которое a[i] + s[t] > upper)
            auto diff1 = lower - nums[i], diff2 = upper - nums[i];
            auto iter_begin = std::lower_bound(std::next(nums.cbegin(), i + 1), nums.cend(), diff1);
            if (iter_begin !=  nums.cend()) {
                auto iter_end = std::lower_bound(iter_begin, nums.cend(), diff2 + 1);
                nums.erase(iter_end, nums.cend());
                if (iter_begin != iter_end) {
                    count += std::distance(iter_begin, iter_end);
                }
            }
        }
        return count;
    }
    int idealArrays(int n, int maxValue) {
        /*
        Нужно найти количество таких массивов отсортированных , что arr[i] = r * arr[i-1], 1 <= arr[i] <= maxValue
        Результат надо вернуть по модулю 10^9 + 7

        Итак, у нас можно сделать таблицу умножений
        от 1 до max_value
        Ставим 1-цы
        На самом деле тут решается жадным выбором задача для меньшего массива
        a1 - может быть любым значением
        dp[n][maxValue];
        dp[0] = {1, ..., 1};
        Половина = sqrt(maxValue)

        */
        if (n == 1)
            return maxValue;
        constexpr unsigned int MOD = 1000000007;
        std::vector<std::vector<unsigned long>> dp(2, std::vector<unsigned long>(maxValue+1, 0));
        int end = std::sqrt(maxValue) + 1;
        unsigned long count = 0;
        for (int j = 0; j <= maxValue; ++j) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < end; ++j) {
                for (int k = maxValue/j; k > j; --k) {
                    dp[1][j*k] += (dp[0][j] + dp[0][k]) % MOD;
                }
                dp[1][j*j] += dp[0][j] % MOD;
            }
            std::swap(dp[0], dp[1]);
            std::fill(dp[1].begin(), dp[1].end(), 0);
        }
        for (int j = 1; j <= maxValue; ++j) {
            count = (count + dp[0][j]) % MOD;
        }
        return static_cast<int>(count);
    }
    int idealArray2(int n, int maxValue) {
        /*
        Итак, end - это количество простых делителей
        log2(maxValue) - максимальное количество простых делителей для чисел <= maxValue
        Итак нам надо найти количество перестановок с повторениями (r1, r2, ..., rk) + {1}x(n-1) с повторениями
        Таким образом алгоритм с использованием решета Эратосфена
        Для каждого числа k
        если таблица era помечаемых чисел
        есть вектор dp, хранящий все ранее найденные произведения (dp.reserve(maxValue))
        есть вектор tp, который хранит количества найденных простых множителей (пары <множитель:количество>)

        Прикол:
        Я исследовал задачу
        количество массивов можно предcтавить каким-то многочленом степени [log2n]

        Забавный факт, обнаруженный при наблюдениях:
        если maxValue простое число, то f(n, maxValue) = n + f(n, maxValue-1)
        f(1, maxValue) = maxValue
        f(n, 1) = 1
        Ещё в ходе исследования было обнаружено,
        Итак, ищем максимальную степень двойку числа maxValue
        Далее, 
        Допустим
        Например при n = 7
        первое число 1
        к нему прибавляются следующие разности
        [7, 7, 28,        7, 49,     7, 84,           28,        49,     7, 196,          7, 49,     49,     210,          7, 196,          7, 196,          49,     49,     7, 588,             28,        49,     84,           196,          7, 343,       7, 462]
        разложение:
        [7, 7, [2, 2, 7], 7, [7, 7], 7, [2, 2, 3, 7], [2, 2, 7], [7, 7], 7, [2, 2, 7, 7], 7, [7, 7], [7, 7], [2, 3, 5, 7], 7, [2, 2, 7, 7], 7, [2, 2, 7, 7], [7, 7], [7, 7], 7, [2, 2, 3, 7, 7], [2, 2, 7], [7, 7], [2, 2, 3, 7], [2, 2, 7, 7], 7, [7, 7, 7], 7, [2, 3, 7, 11]]
        соответствующий maxValue
        [2, 3, 4,         5, 6,      7, 8,            9,         10,     11,12,           13, 14,    15,     16,           17,18,           19,20,           21,     22,     23,24,              25,        26,     27,           28,           29,30,        31,32]

        Посмотреть аналоги для n = 2
        [2, 2, [3],       2, [2, 2], 2, [2, 2],       [3],       [2,2],  2, [2,3],        2,  [2,2], [2,2],  [5],          2, [2,3],        2, [2,3],        [2, 2], 4,      2, [2,2,2],         [3],       [2,2],  [2,2],        [2,3],        2, [2,2,2],   2, [2,3]]
        n = 3
        [3, 3, [2*3],     3, [3, 3], 3, [2, 5],       [2,3],     [3,3],  3, [2,3,3],      3,  [3,3], [3,3],  [3,5],        3, [2,3,3],      3, [2,3,3],      [3, 3], [3, 3], 3, [2,3,5],         [2,3],     [3,3],  [2, 5],       [2,3,3],      3, [3,3,3],   3, [3,7]]

        Короче, ищем значения f(maxValue = x0, n) для n=1...[log2n]+1 при помощи моего первого метода, затем ищем интерполяционный многочлен
        1) Ищем конечные разности
        [g(x0), g(x0, x1), ..., g(x0, x1, ..., x(log2n))]
        2) Записываем произведения вида (n-1), (n-1)(n-2)/2, (n-1)(n-2)(n-3)/6,..., (n-1)...(n-k)/k!
        В связи с тем, что мы используем кольца вычетов, нужно заранее узнать какой член делится k,
        Для этого сразу записываем массив (n-1),(n-2),...,(n-k) и на каждой итерации i находим первое значение, которое делится на i, обновляем, затем
        умножаем первые 
        */
        if (n == 1)
            return maxValue;
        constexpr unsigned int MOD = 1000000007;
        std::vector<std::vector<unsigned long>> dp(2, std::vector<unsigned long>(maxValue+1, 0));
        int end = std::sqrt(maxValue) + 1;
        int koeff_cnt = std::min(static_cast<int>(std::log2(maxValue)), n);
        std::vector<long> fn(koeff_cnt+1, 0);
        std::vector<long> gn, delta(fn.size()-1);
        long result = 0;
        long tmp = 0;
        int jk = 0;
        for (int j = 0; j <= maxValue; ++j) {
            dp[0][j] = 1;
        }
        fn[0] = maxValue;
        
        //TODO: заменить j * k на jk, чтобы результат обрабатывать по модулю
        for (int i = 1; i <= koeff_cnt; ++i) {
            for (int j = 1; j < end; ++j) {
                for (int k = maxValue/j; k > j; --k) {
                    jk = j * k;
                    tmp = (dp[0][j] + dp[0][k]);
                    dp[1][jk] = (dp[1][jk] + tmp) % MOD;
                    fn[i] = (fn[i] + tmp) % MOD;
                }
                tmp = dp[0][j];
                jk = j * j;
                dp[1][jk] = (dp[1][jk] + tmp) % MOD;
                fn[i] = (fn[i] + tmp) % MOD;
            }
            std::swap(dp[0], dp[1]);
            std::fill(dp[1].begin(), dp[1].end(), 0);
        }
        //Новая часть
        gn = fn;
        if (koeff_cnt < n) {
            for (unsigned int i = 0; i < gn.size(); ++i) {
                for (unsigned int j = gn.size()-1; j > i; --j) {
                    if (gn[j] < gn[j-1]) {
                        gn[j] += MOD;
                    }
                    gn[j] = gn[j] - gn[j - 1];
                }
            }
            for (unsigned int i = 1; i <= delta.size(); ++i){
                delta[i-1] = n - i;
            }
            for (int i = 0; i <= delta.size(); ++i) {
                long mult = 1;
                int mn = i;
                int gcd_r;
                for (unsigned int j = 0; j < i; ++j) {
                    gcd_r = std::gcd(mn, delta[j]);
                    delta[j] /= gcd_r;
                    mn /= gcd_r;
                    mult = (mult * delta[j]) % MOD;
                }
                result = (result + (mult * gn[i])) % MOD;
            }
        } else {
            result = fn[koeff_cnt-1];
        }
        return result;
    }
};

#include <iostream>
int main(void) {
    //std::vector<int> nums1{2, 0, 2, 0}, nums2{1, 4}, nums{2,1,3,4,5,2}, numsr1{0,1,7,4,4,5}, numsr2{1,7,9,2,5};
    //std::cout << Solution().minSum(nums1, nums2) << std::endl;
    //std::cout << Solution().findScore(nums) << std::endl;
    //std::cout << Solution().countFairPairs(numsr1, 3, 6) << std::endl;
    //std::cout << Solution().countFairPairs(numsr2, 11, 11) << std::endl;;
    //std::cout << Solution().countFairPairs(nums, -100, 100) << std::endl;;
    //TODO: Должно быть 5 + 4 + 3 + 2 + 1 = 15
    auto sol = Solution();
    /*
    constexpr int n_begin = 1, n_end = 15;
    for (int n = n_begin; n <= n_end; ++n) {
        std::cout << n << '\t';
    }
    std::cout << std::endl;
    for (int n = n_begin; n <= n_end; ++n) {
        std::cout << sol.idealArrays(n, 84) << '\t';
    }
    std::cout << std::endl;
    for (int n = n_begin; n <= n_end; ++n) {
        std::cout << sol.idealArray2(n, 84) << '\t';
    }
    std::cout << std::endl;
    for (int maxValue = 1; maxValue <= 100; ++maxValue) {
        for (int n = 1; n <= 100; ++n) {
            auto result1 = sol.idealArrays(n, maxValue);
            auto result2 = sol.idealArray2(n, maxValue);
            if (result1 != result2) {
                std::cout << maxValue << ':' << n << ":\t" << result1 << '\t' << result2 << std::endl;
            }
        }
    }
    */
    std::cout << sol.idealArray2(2747, 5606) << std::endl;
    std::cout << sol.idealArrays(2747, 5606) << std::endl;
    /*
    */
    /* maxValue = 1, f(n) = 1
       maxValue = 2, f(n) = 1 + n
       maxValue = 3, f(n) = 1 + 2n
       maxValue = 4, f(n) = 4 + (n-1)*4 + (n-1)(n-2)/2 = 4n + (n^2 - 3n + 2) / 2 = 1 + 2.5n + (n^2) / 2 = (2 + 5n + n^2) / 2
       g(x1) = 4 
       g(x2, x1) = 4
       g(x3, x2, x1) = 1
       maxValue = 7, f(n) = 7 + (n-1)*9 + 3(n-1)(n-2)/2 = 9n - 2 + (3n^2 - 9n + 6) / 2 = (3n^2 + 9n + 2) / 2
       g(x1) = 7
       g(x1, x2) = 9
       g(x1, x2, x3) = 3
       maxValue = 10,f(n) = 10 +(n-1)*17+ 9(n-1)(n-2)/2 + (n-1)(n-2)(n-3)/3 = -7 + 17n + (9n^2 - 27n + 18)/2 + (n^2 - 3n + 2)(n-3)/3 = 
       g(x1) = 10
    */
    return 0;
}