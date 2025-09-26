#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <numeric>
#include <unordered_set>
#include <map>
#include <array>

/*
//TODO: Позже доделай
Третья попытка решить задачу через динамическое программирование
Итак, у нас дан набор цифр длиной count, для каждой цифры мы можем
Нам нужно посчитать сколько
59123163973
У нас есть матрица dp[i][l][sum] - она хранит в себе индексы j_1 следующих элементов, для которых dp[j_1][l-1][sum-A_{j_1}] рекурсивно хранит тоже самое
либо на 
массив A с элементами A[i]
Алгоритм
Итак, берём последние count / 2 и вычисляем dp[i][1][a[i]] = index_end
dp[i][l][sum] - массив индексов элементов [i_1, ..., i_k], которые могут быть частью решения, рекурсивно потом для каждого отдельного i_r продолжаем искать dp[i_r][l-1][sum-a[i]]
для dp[i_r][1][sum] sum всегда = a_{i_r}
желательно a_i упорядочить, чтобы учитывать повторения элементов
для вычисления количества перестановок используем массив permuts
через dp[i][l]
*/

/*
Попробуем подумать в следующем ключе
Итак, допустим мы решаем задачу без использования meet-in-the-middle
Нам нужно найти количество всех таких чисел, что сумма цифр на четной позиции == сумме на нечетных позициях
в случае если количество разрядов нечетное, то тут и без meet-in-the-middle можно обойтись
В случае четных чисел нужен meet-in-the-middle
В случае если мы решаем при помощи dp, то нужно как-то хранить состояния

Рассмотрим пример:
59123163973
11233356799
99765333211
[2]9,[1]7,[1]6,[1]5,[3]3,[1]2,[2]1

Наверное нужно создать какую-тaструктуру данных
permut[i][count1][count2][sum1][sum2] - кол-во перестановок на i-м типе цифры, с количеством ранее(+ i-е цифры) используемых чисел count
counts[i] - количества встреченных цифр i
permut[i][count1][count2]
comb[i][count1][count2] - количество таких сочетаний
sums[i][count1][count2][sum1];
dp[count1][count2][sum1] - количество таких перестановок, что количество 
1:6:dp[count1][count2][sum1] = dp[count1][count2-6][sum1]+dp[count1-1][count2-5][sum1-1] + ... + dp[count1-6][count2][sum1-6]

Так у нас получается 6^80 вычислений, че-то многовато...
dp[sum1][count1][count2][r] - (r < 2, мы для каждого состояния считаем 2 количества перестановок)


for (int i = 0; i < 10; ++i){
    for (int j = 0; j < counts[i];++j){
        for (int cnt = 0; cnt <= accum; ++cnt) {

        }
    }
}
*/
class Solution {
private:
    #define DIGIT_COUNT 10
    #define MAX_ELEMENT_COUNT 40
    #define SUM_MAXIMUM 360
public:
    int countBalancedPermutations(std::string num) {
        int dp[SUM_MAXIMUM][MAX_ELEMENT_COUNT][MAX_ELEMENT_COUNT][2] = {0};
        int counts[DIGIT_COUNT] = {0}, max_count = num.size()/2 + num.size()%2, current_count = 0, all_count = 0, sum1;
        for (const auto &digit : num) {
            ++counts[digit-'0'];
        }
        int i = 0;
        while (!counts[i]) {
            ++i;
        }
        current_count = counts[i];
        for (int count1 = std::min(current_count, max_count); count1 >= 0; --count1) {
            sum1 = count1*i;
            dp[sum1][count1][current_count-count1][0] = 1;
            dp[sum1][count1][current_count-count1][1] = 1;
        }
        for (; i < 10; ++i) {
            if (counts)
        }
    }
};


//////////////////////////////////////////////ПОПЫТКИ РЕШИТЬ ЗАДАЧУ ЧЕРЕЗ БЕКТРЕКИНГ
/*
Это попытка решить задачу через бектрекинг
Итак, у нас задача найти все такие перестановки чисел, где сумма чисел на четной позиции = сумме чисел на нечётной
Переформулируем иначе
Пусть S = половина суммы цифр числа
Мы ищем 2 непересекающихся упорядоченных множества, каждое которое состоит из половины цифр изнчального множества I
Скажем, одно упорядоченное множество A >= B - другого можнество (они оба должны быть равны по мощности), если соответствующие элементы из первого можества a_i >= b_i соответвтствующего из другого
Множество I - множество всех элементов
Нам нужно при помощи бектрекинга определить все такие A >= sort(I/A), |A| = |I|/2 + |I|%2, Sum(A) = S
Задача удовлетворения ограничений:
Переменные A = (a_1, ..., a_{n/2 + n%2}), B = (b_1, ..., b_{n/2})
Домены: D_i = I
Ограничения:
A не пересекается с B,
A U B = I,
A (соответственно и B) должны быть уникальными
A >= B,
sum(A) = sum(B) = S

На их основе введем новые ограничения

i <= n/2 + n%2
C1)Если a_i = target, то следующие ak = 0, k = (i+1)..(n/2 + n%2), если условие выполняется, значит решение найдено
C2)Если a_i > target, то пропускаем
C3)Проблема дублирования решений, для расширения частичного решения не брать из множества I элемент, похожий на тот элемент, который расширял решение до возврата.
C4)Если сумма любых r следующих элементов из k элементов подмножества < t, (t-оставшаяся нужная сумма, которую необходимо достигнуть)
 то достигнут тупик, просматривать дальнейшие решения не имеет смысла (упорядочиваем в обратном порядке и каждый suffix[i][r] = сумме r следующих элементов, начиная с i)
C5)Для каждого подмножества I1 \in I храним массив хеш-таблиц, где каждая l-я таблица (prohibited[i][l]) хранит в себе недостижимые суммы из l значений
(В реализации будем хранить матрицу таблиц, которая не покрывает всего этого множества, но возможно позволит отсечь ненужные решения).
С6)для оставшихся r элементов решения, должно оставться подмножество I1: |I1| >= r

Одна из проблем - мы оперируем не массивом чисел, а массивом их количеств, как определиться с суффиксом?
Одно из решений - во время обхода для каждого состояния решения хранить текущие значение index (количество чисел слева (включая I[index]) в упорядоченном I), current_num - цифра, на которой мы остановились

C5 - вместо матрицы таблиц удобно хранить просто матрицу prohibited[target][l] в которой каждый элемент - это индекс элемента, начиная с которого сумма l элементов не достигает target
таким образом, ограничение C5 выполняется i < prohibited[target][l]

*/

//#define _DEBUG 1
//#define _PROHIBIT_ON 1

//Эта версия подойдет для задачи count_balancing
//TODO: Вместе с prohibited можно использовать закешированные решения для участка (допустим для target и i мы уже находили решение, может его сохранить, чтобы заново не вычислять?)
//Это решение на основе бектрекинга, оно не эффэктивно, нам же нужно искать не сами решения, а их количество
class Solution2 {
private:
    #define TABLE_SIZE 384
    #define MOD 1000000007
    #ifdef _DEBUG
    std::ofstream stream;
    long long sets_count;
    #endif
    int counts[10];
    int curr_counts[10];
    long permut_count;
    int index_end;
    std::size_t elements_count;
    int sum;
    std::vector<std::vector<int>> suffixes;
    //TODO: Может вместо таблиц использовать просто массивы размером TABLE_SIZE 
    #ifdef _PROHIBIT_ON
    //std::vector<std::vector<std::unordered_set<int>>> prohibited;
    std::vector<std::vector<int>> prohibited;
    #endif
    #ifdef _DEBUG
    void _print_counts(int curr_counts[10]) {
        for (int i = 9; i >= 0; --i) {
            for (int j = curr_counts[i]; j > 0; --j) {
                stream << i;
            }
        }
        stream << std::endl;
    }
    #endif
    int _checkCounts() {
        for (int i = 9; i >= 0; --i) {
            if (curr_counts[i] > counts[i]) {
                return 1;
            }
            if (curr_counts[i] < counts[i]) {
                return -1;
            }
        }
        return 0;
    }
    //TODO: Вроде есть более быстрое вычисление большого числа перестановок
    long _countPermutations(int chosen_counts[10], std::size_t nums_count) {
        if (elements_count == 0) {
            return 0;
        }
        long result = 1;
        int tmp = 0, tmp_count = 0;
        std::vector<int> N_vector(nums_count);
        for (std::size_t i = 0; i < nums_count; ++i) {
            N_vector[i] = i+1;
        }
        for (int i = 0; i < 10; ++i) {
            for (int sub_count = chosen_counts[i]; sub_count; --sub_count) {
                tmp_count = sub_count;
                for (auto &element : N_vector) {
                    if (tmp_count == 1) {
                        break;
                    }
                    tmp = std::gcd(element, tmp_count);
                    if (tmp > 1) {
                        element /= tmp;
                        tmp_count /= tmp;
                    }
                }
            }
        }
        for (const auto &element : N_vector) {
            result = (result * element) % MOD;
        }
        return result;
    }
    enum BACKTRACK_STATE {
        DEAD_END = 0x00,
        SOLUTION_END = 0x01,
        BACKTRACK_END = 0x02,
    };
    void fun() {
        std::cout << "Bruh" << std::endl;
    }
    int backtrack1(int target, int current_num, int index, std::size_t current_count) {
        if (!current_count) {
            #ifdef _DEBUG
            sets_count++;
            #endif
            if (target == 0) {
                #ifdef _DEBUG
                //std::cout << "New:" << std::endl;
                //std::cout << "curr_counts:" << std::endl;
                _print_counts(curr_counts); 
                //std::cout << "counts:" << std::endl;
                //_print_counts(counts);
                //std::cout << "p_count:\n" << p_count << std::endl << std::endl;
                #endif
                permut_count = (((_countPermutations(curr_counts, elements_count) *_countPermutations(counts, elements_count+1)) % MOD) + permut_count) % MOD;
                return SOLUTION_END;
            }
            return DEAD_END;
        }
        int i = index;
        int solution_found = DEAD_END;
        //C2
        for (; current_num >= 0 && (target < current_num || !counts[current_num]); i += counts[current_num], --current_num);
        //C6
        for (; !(solution_found & BACKTRACK_END) && current_num >= 0 && i < index_end - current_count + 1; i += counts[current_num], --current_num) {
            //C5 и C4
            #ifdef _PROHIBIT_ON
            if (i < prohibited[target][current_count] && target <= suffixes[i][current_count]) {
            #else
            if (target <= suffixes[i][current_count]) {
            #endif
                if (counts[current_num]) {
                    ++curr_counts[current_num];
                    --counts[current_num];
                    solution_found |= backtrack1(target - current_num, current_num, i+1, current_count-1);
                    ++counts[current_num];
                    --curr_counts[current_num];
                }
            } else {
                break;
            }
        }
        #ifdef _PROHIBIT_ON
        if (!(solution_found & SOLUTION_END) && prohibited[target][current_count] > index) {
            prohibited[target][current_count] = index;
        }
        #endif
        return solution_found;
    }
    int backtrack2(int target, int current_num, int index, std::size_t current_count) {
        if (!current_count) {
            #ifdef _DEBUG
            sets_count++;
            #endif
            int check = _checkCounts();
            if (check < 0) {
                return BACKTRACK_END;
            }
            if (target == 0) {
                #ifdef _DEBUG
                //std::cout << "New:" << std::endl;
                //std::cout << "curr_counts:" << std::endl;
                _print_counts(curr_counts); 
                //std::cout << "counts:" << std::endl;
                //_print_counts(counts);
                //std::cout << "p_count:\n" << p_count << std::endl << std::endl;
                #endif
                if (check) {
                    permut_count = ((((_countPermutations(curr_counts, elements_count) *_countPermutations(counts, elements_count)) % MOD) * 2) % MOD + permut_count) % MOD;
                } else {
                    long tmp = _countPermutations(curr_counts, elements_count);
                    permut_count = (((tmp * tmp) % MOD) + permut_count) % MOD;
                }
                return SOLUTION_END;
            }
            return DEAD_END;
        }
        //target - оставшаяся часть суммы
        int i = index;
        int solution_found = DEAD_END;
        //C2
        for (; current_num >= 0 && (target < current_num || !counts[current_num]); i += counts[current_num], --current_num);
        //C6
        for (; !(solution_found & BACKTRACK_END) && current_num >= 0 && i < index_end - current_count + 1; i += counts[current_num], --current_num) {
            //C5 и C4
            #ifdef _PROHIBIT_ON
            if (i < prohibited[target][current_count] && target <= suffixes[i][current_count]) {
            #else
            if (target <= suffixes[i][current_count]) {
            #endif
                if (counts[current_num]) {
                    ++curr_counts[current_num];
                    --counts[current_num];
                    solution_found |= backtrack2(target - current_num, current_num, i+1, current_count-1);
                    ++counts[current_num];
                    --curr_counts[current_num];
                }
            } else {
                break;
            }
        }
        if (solution_found & BACKTRACK_END) {
            return BACKTRACK_END;
        }
        #ifdef _PROHIBIT_ON
        if (!(solution_found & SOLUTION_END) && prohibited[target][current_count] > index) {
            prohibited[target][current_count] = index;
        }
        #endif
        return solution_found;
    }
    bool prepare_structs(std::string &str) {
        for (std::size_t i = 0; i < 10; ++i) {
            curr_counts[i] = 0;
            counts[i] = 0;
        }
        for (const auto &sym : str) {
            ++counts[sym - '0'];
        }
        #ifdef _DEBUG
        sets_count = 0;
        #endif
        elements_count = str.size() / 2;
        index_end = static_cast<int>(str.size());
        suffixes.resize(str.size(), std::vector<int>(str.size()+1, 0));
        int accum = 0;
        for (int current_num = 0, i = index_end-1; current_num < 10; ++current_num) {
            for (int count = counts[current_num]; count > 0; --count, --i) {
                accum += current_num;
                suffixes[i][index_end-i] = accum;
                for (int j = index_end - i - 1; j > 0; --j) {
                    //TODO: Мне кажется тут проблема с индексами, но возможно и нет
                    suffixes[i][j] = suffixes[i][j+1] - suffixes[i+j][1];
                }
            }
        }
        if (accum & 1) {
            return false;
        }
        #ifdef _PROHIBIT_ON
        prohibited.resize(accum + 1, std::vector<int>(elements_count+1, index_end));
        #endif
        permut_count = 0;
        sum = accum / 2;
        return true;
    }
public:
        int countBalancedPermutations(std::string num) {
        if (!num.size()) {
            return 0;
        }
        if (num.size() == 1) {
            if (num[0] == '0') {
                return 1;
            } else {
                return 0;
            }
        }
        if (!prepare_structs(num)) {
            return 0;
        }
        if (num.size() & 1) {
            backtrack1(sum, 9, 0, elements_count);
        } else {
            backtrack2(sum, 9, 0, elements_count);
        }
        #ifdef _DEBUG
        stream << "Count:" << sets_count << std::endl;
        #endif
        return static_cast<int>(permut_count);
    }
    #ifdef _DEBUG
    Solution():stream{"tmp.txt"}{};
    #endif
};
/*
    Боже как же я ненавижу вот эти вот задачи с большими числами
    Ошибка сейчас - превышено максимальное время выполнения, хотя по замерам там 155 ms для числа с 52 разрядами
    Тут явно напрашивается изменение _buildSum1, _buildSum2 с обрезанием ненужных вариантов
    Итак, допустим у нас есть невозрастающая последовательность
    s = a_1,a_2,...,a_{i-1},a_i,a_{i+1},...,a_{n}
    Пусть X_n = [b_1, b_2,..., b_m] - оставшиеся элементы в порядке убывания
    
    Операция сдвига назад move(s, i, b) = s_i = a_1,...,a_{i-1},a{i+1},...,a_{n},b
    Сумма изменилась на значение delta = b - a_{i}, при этом если delta отрицательная, то большую сумму получить невозможно
    Ну вот допустим, мы не смогли разобраться с этим числом
    Итак, в начале строим первое число, с которого начинаем поиск
    То есть мы выписываем сначала наибольшие числа, сумма которых >=sum, затем записываем оставшиеся наименьшие числа
    Что-то типо 99999988877721111111000000 в моем случае
    Итак, берём 72 как центральную часть
    Итак, мы знаем, что с 2-ки начинается минимальная часть справа
    средняя часть - это переходная 7-ка
    левее её максимальная часть
    Итак, всё что мы делаем - это балансируем среднюю часть, либо расширяем её влево и вправо
    Но нам нужно определить операцию балансировки

    Итак, у нас есть 3 отрезка - старший, балансируемый, и младший
    Возвращаемся к теме сдвигов
    99999988877721111111000000
    99999988877221111111000000 - 103
    99999988877521111111000000 - 106
    сдвиги влево к 5 не сделаешь
    5 превращаем в 4, и тогда либо меняем следующие несколько элементов на большие
    99999988877431111111000000
    либо сделать сдвиг вправо
    99999988877422111111100000
    Итак, нужно определить критерий и правило, по которому мы изменяем следующе элементы на большие
    Вот было число
    99999988877521111111000000 - наибольшее допустимое число
    |
    99999988877431111111000000
    |
    99999988877422111111100000
    Ну вот допустим, мы просматриваем число где-то через
    Итак, попробуем следующее
    Мы построим всю последовательность в порядке убывания
    dp[i][k] - сумма k элементов начиная с i
    Тогда в начале ставим cur_sum = dp[0][k] + dp[N-k-1][N/2-k] начальная сумма
    
    Тогда пробуем решить задачу о рюкзаке, где мы должны взять такие i_1,...,i_r и k_1,...,k_r,
    что 
    k_1 + ... + k_r = N/2, все k_j > 0
    dp[i_1][k_1] + ... + dp[i_r][k_r] = sum / 2

    Похоже, что и здесь нужно заранее прописывать ещё какие-то префиксы и суффиксы
    Итак, примитивный алгоритм
    f() {
    Берём первые N / 2 элементы невозрастающей последовательности
    }
    //Функция, которая находит 
    g(j, k, dp, sum) {
        Если dp[j][k] < sum:
            Здесь наверное можно обновить префикс с верхней границей суммы, на
        Если dp[j][k] == sum:
            Записываем новое решение, считаем количества перестановок
        Если dp[j][k] > sum:
            Тогда для 
    }
    //TODO: Проблема dp[i][k] может быть равна dp[i+1][k]




    2054317243015173094298744484833032171907497216399610
    отсортировать:
    9999998887777776655444444443333333222221111111000000
    Первое число:
    99999988877721111111000000
    Первое число строится по правилу сначала k самых больших, где их сумма - максимальная сумма < sum / 2 (TODO: А если равна)
    Далее, берутся оставшиеся наименьшие
    Можно построить матрицу dp, где dp[pos][count] = суммен count элементов начиная с позиции pos в отсортированном в обратном порядке массиве (сверху)
    Таким образом задача сводится к поиску таких сумм dp[pos_1][k_1] + dp[pos_2][k_2] + ... dp[pos_r][k_r] = sum / 2, где k_1 + ... + k_r = n / 2
    Как ускорить поиск? 
    Мы можем сохранять позиции dp[pos][count] = weight в хеш-таблице, которая по weight, count и нижней границе pos, находит новый pos, который подходит
    хеш-таблица и двоичное дерево, в дереве сравнивается 
    или может вообще построить матрицу (не хеш-таблицу), dp2[weights][count], элементы которой являются деревьями поиска с ключами pos

    Итак, если отсортировать
    Ну допустим мы отсортировали значения по убыванию. 
    Мы храним dp[pos][count] - выбрали 
    Далее, справа мы имеем специальные суффиксы, которые хранят в себе нижнюю границу накапливаемой суммы, которая получается при суммировании dp[pos][count] слева от суффикса s[i]
    Возможно для этого пожалуй стоит добавить и верхнюю границу
    Ещё одна проблема - повторения значений dp[pos][count] для разных pos (допустим в строке 333333 pos = 0 или 3 и count = 3)
    
*/

//#define _DEBUG

class Solution1 {
    private:
        #define MOD 1000000007
        int _N_max = 0;
        #ifdef _DEBUG
        std::ofstream stream;
        long long sets_count;
        #endif
        //TODO: возможно можно как-то кэшировать результаты без дополнительных вычислений одинаковых перестановок
        //TODO: 
        long _countPermutations(const int curr_counts[10], const int N) {
            if (N == 0) {
                return 0;
            }
            long result = 1;
            int tmp = 0, tmp_count = 0;
            std::vector<int> N_vector(N);
            for (int i = 0; i < N; ++i) {
                N_vector[i] = i+1;
            }
            for (int i = 0; i < 10; ++i) {
                for (int sub_count = curr_counts[i]; sub_count; --sub_count) {
                    tmp_count = sub_count;
                    for (auto &element : N_vector) {
                        if (tmp_count == 1) {
                            break;
                        }
                        tmp = std::gcd(element, tmp_count);
                        if (tmp > 1) {
                            element /= tmp;
                            tmp_count /= tmp;
                        }
                    }
                }
            }
            for (const auto &element : N_vector) {
                result = (result * element) % MOD;
            }
            return result;
        }
        void _buildNumber1(int n, int counts[10], int curr_counts[10], int curr_sum, int last, int sum, int &p_count) {
            //TODO: Надо как-то обрывать варианты в случае curr_sum < sum
            if (!n) {
                #ifdef _DEBUG
                sets_count++;
                #endif
                if (curr_sum == sum) {
                    p_count = static_cast<int>((((_countPermutations(curr_counts, _N_max) *_countPermutations(counts, _N_max + 1)) % MOD) + p_count) % MOD);
                }
                return;
            }
            int err = 0;
            for (int i = last - 1; i >= 0; --i) {
                if (counts[i]) {
                    counts[i]--;
                    curr_counts[i]++;
                    _buildNumber1(n-1, counts, curr_counts, curr_sum + i, i + 1, sum, p_count);
                    curr_counts[i]--;
                    counts[i]++;
                }
            }
        }
        int _checkCounts(int curr_counts[10], int counts[10]) {
            for (int i = 9; i >= 0; --i) {
                if (curr_counts[i] > counts[i]) {
                    return 1;
                }
                if (curr_counts[i] < counts[i]) {
                    return -1;
                }
            }
            return 0;
        }
        #ifdef _DEBUG
        void _print_counts(int curr_counts[10]) {
            for (int i = 9; i >= 0; --i) {
                for (int j = curr_counts[i]; j > 0; --j) {
                    stream << i;
                }
            }
            stream << std::endl;
        }
        #endif
        int _buildNumber2(int n, int counts[10], int curr_counts[10], int curr_sum, int last, int sum, int &p_count) {
            if (!n) {
                int err = _checkCounts(curr_counts, counts);
                if (err == -1) {
                    return -1;
                }
                #ifdef _DEBUG
                sets_count++;
                #endif
                if (curr_sum == sum) {
                    if (err == 1) {
                        p_count = static_cast<int>(((((_countPermutations(curr_counts, _N_max) *_countPermutations(counts, _N_max)) % MOD) * 2) % MOD + p_count) % MOD);
                        #ifdef _DEBUG
                        //std::cout << "New:" << std::endl;
                        //std::cout << "curr_counts:" << std::endl;
                        _print_counts(curr_counts); 
                        //std::cout << "counts:" << std::endl;
                        //_print_counts(counts);
                        //std::cout << "p_count:\n" << p_count << std::endl << std::endl;
                        #endif
                    } else if (!err) {
                        long result = _countPermutations(curr_counts, _N_max);
                        p_count = static_cast<int>(((result * result) % MOD + p_count) % MOD);
                        #ifdef _DEBUG
                        //std::cout << "New:" << std::endl;
                        //std::cout << "curr_counts:" << std::endl;
                        _print_counts(curr_counts); 
                        //std::cout << "counts:" << std::endl;
                        //_print_counts(counts);
                        //std::cout << "result:\n" << result << std::endl;
                        //std::cout << "p_count:\n" << p_count << std::endl << std::endl;
                        #endif
                    }
                    return 0;
                } else {
                    return 1;
                }
            }
            int err = 0;
            for (int i = last - 1; i >= 0; --i) {
                if (counts[i]) {
                    counts[i]--;
                    curr_counts[i]++;
                    err = _buildNumber2(n-1, counts, curr_counts, curr_sum + i, i + 1, sum, p_count);
                    if (err == -1) {
                        return -1;
                    }
                    curr_counts[i]--;
                    counts[i]++;
                }
            }
            return 0;
        }
    public:
        int countBalancedPermutations(std::string num) {
            int sum = 0;
            int counts[10] = {0}, curr_counts[10] = {0};
            int p_count = 0;
            const auto N = num.size();
            for (const auto &digit : num) {
                counts[digit - '0']++;
                sum += digit - '0';
            }
            if (sum & 1) {
                return 0;
            }
            sum = sum / 2;
            _N_max = N / 2;
            if (N & 1) {
                _buildNumber1(_N_max, counts, curr_counts, 0, 10, sum, p_count);
            } else {
                _buildNumber2(_N_max, counts, curr_counts, 0, 10, sum, p_count);
            }
            #ifdef _DEBUG
            stream << "Count:" << sets_count << std::endl;
            #endif
            return p_count;
        }
        #ifdef _DEBUG
        Solution1():stream{"tmp1.txt"},sets_count{0}{};
        #endif
};

#include <chrono>

int main(void) {
    Solution sol;
    Solution1 sol1;
    /*
    std::string num1 {"123"}, num2 {"112"}, num3 {"12345"}, num4 {"122113"};
    std::cout << sol.countBalancedPermutations(num1) << std::endl;   
    std::cout << sol.countBalancedPermutations(num2) << std::endl;   
    std::cout << sol.countBalancedPermutations(num3) << std::endl;   
    std::cout << sol.countBalancedPermutations(num4) << std::endl;
    */
    //std::cout << sol.countBalancedPermutations("123") << std::endl;
    //std::cout << sol.countBalancedPermutations("112") << std::endl;
    //std::cout << sol.countBalancedPermutations("12345") << std::endl;
    //std::cout << sol.countBalancedPermutations("907229351353920524720924038969") << std::endl;
    //std::cout << sol1.countBalancedPermutations("907229351353920524720924038969") << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    sol.countBalancedPermutations("4197954694239804459909521504934452405578796435660138517");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    #ifdef _PROHIBIT_ON
    std::cout << "Время с включенной таблицей prohibited:" << duration.count() << " ms" << std::endl;
    #else
    std::cout << "Время с отключенной таблицей prohibited:" << duration.count() << " ms" << std::endl;
    #endif
    //std::cout << sol.countBalancedPermutations("4197954694239804459909521504934452405578796435660138517") << std::endl;
    //std::cout << sol.countBalancedPermutations("9072293513539204") << std::endl;
    //std::cout << sol1.countBalancedPermutations("9072293513539204") << std::endl;
    //std::cout << sol.countBalancedPermutations("12345") << std::endl;
    //(122113) - (1 2 2), (1 1 3) -> слева перестановок 3, справа 3 -> 18
    return 0;
}