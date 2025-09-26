#include <vector>
#include <algorithm>
#include <unordered_set>


//SUCCESS, 7ms, побеждает 32,62 %
/*
Вот решение за 0ms
Я вот использовал хеш-таблицу недостижимых значений, а это наивное решение, тупо перебор всех вариантов, моё все равно лучше...

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int n = candidates.size();
        vector<int> comb;
        vector<vector<int>> res;
        function<void(int, int, vector<int>&)> rec = [&](int index, int sum, vector<int> &comb){
            if (sum == target){
                res.push_back(comb);
            }
            
            for (; index < n; index++){
                if (sum + candidates[index] <= target){
                    comb.push_back(candidates[index]);
                    rec(index, sum + candidates[index], comb);
                    comb.pop_back();
                }
            }
        };

        rec(0, 0, comb);

        return res;
    }
};
*/

class Solution {
private:
    #define TABLE_SIZE 64
    std::size_t global_n;
    std::size_t last_i;
    std::vector<std::vector<int>> result;
    std::vector<std::unordered_set<int>> prohibited;
    std::vector<int> nums;
    std::vector<int> cands;
    /*
    Проблема, я здесь не могу использовать ни suffix[i], ни prohibited[i]
    Таким образом, это задача на самом деле выглядит несколько иначе
    Даны переменные X = (x_1, ..., x_n)
    Каждая переменная по сути имеет независимый домен D_i = D_j = candidates
    Ограничения вроде выглядят также:
    x_i = target или x_i + x_j = target или ... или Sum(X) = target
    С1,С2,C3 работают как и прежде
    C4 не работает
    С5 может сработать, хоть переменная может повторяться, но всё же из сколько угодно комбинаций 
    сколько угодного количества следующих чисел нельзя сделать сумму = target, значит нельзя повторить
    */
    bool backtrack(int target, std::size_t current_i) {
        std::size_t i = current_i;
        bool solution_found = false;
        //C2
        for (; i < global_n && target < cands[i]; ++i);
        for (; i < global_n; ++i) {
            //C5
            if (prohibited[i].find(target) == prohibited[i].cend()) {
                //C1
                if (target == cands[i]) {
                    nums.push_back(cands[i]);
                    result.push_back(nums);
                    nums.pop_back();
                    solution_found = true;
                } else if (target > cands[i]) {
                    nums.push_back(cands[i]);
                    solution_found |= backtrack(target - cands[i], i);
                    nums.pop_back();
                }
                //C3 выполняется автоматически через инкремент i
            } else {
                break;
            }
        }
        if (!solution_found) {
            prohibited[current_i].insert(target);
            return false;
        }
        return true;
    }
    void prepare_arrays(std::vector<int> &candidates) {
        cands = std::move(candidates);
        std::sort(cands.rbegin(), cands.rend());
        prohibited.resize(cands.size());
        result.clear();
        for (auto &element : prohibited) {
            element.reserve(TABLE_SIZE);
        }
        nums.reserve(cands.size());
        global_n = cands.size();
    }
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        if (!candidates.size()) {
            return {};
        }
        prepare_arrays(candidates);
        backtrack(target, 0);
        return result;
    }
};

#include <iostream>

int main(void) {
    std::vector<int> candidates = {7, 3, 2};
    Solution sol;
    auto result = sol.combinationSum(candidates, 18);
    for (const auto &subvector : result) {
        for (const auto &element : subvector) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << result.size() << std::endl;
    return 0;
}
        /*
        Итак, дан массив candidates, нужно найти в нём такие наборы (неупорядоченные) чисел, сумма которых равна target
        Итак, рассмотрим её как задачу ограничения
        А вот как её представить как задачу CSP?
        Ну допустим есть
        переменные: x_1, ..., x_{candidates.size()}
        домены: D_i = {candidates[i]}
        ограничения: 
        x1 == target или x2 == target ...или xi == target
        или x1+x2 == target .....
        ....
        или x1 + ... + xn == target

        Надо сузить область поиска:
        C1)если xi = target - пометить xi как решение, (но не выбрасываем ограничения, могут быть 0)
        C2)если xi > target - xi игнорируем, выбрасываем её из ограничений
        C3)Далее, если уже нашли все расширяемые решения для какого-то частичного решения partial_sol(X) = (x_{i_1}, x_{i_2}, ..., x_{i_k}), то после сокращения
        этого решения на какой-то элемент x_{i_p}, в последующих расширенных решений решения partial_sol(X)/x_{i_p} не должно содержаться x_{i_p}. 
        Для этого лучше предварительно упорядочить массив candidates в обратном порядке.

        Тогда первые члены будут > target,
        А поиск суммы начинаем с первого слева элемента <= target.
        В случае нескольких подряд идущих одинаковых элементов, начинаем с последнего такого и строим идем обратно, короче выбираем максимальное такое количество одинаковых элементов с конца так, чтобы
        сумма была <= subtarget

        Ещё можно будет срезать так:
        C4)если последние k элементов <= b и k * b < subtarget, то достигнут тупик
        Для этого можно создать дополнительный массив suffix[i] = сумма последних элементов массива начиная с i.
        C5)как вариант для каждого оставшегося X/partial_sol(X) можно хранить отрицательные домены, (какую-нибудь хеш-таблицу, в которую будем записывать какое-то недостижимое значение target для подмножества)
        Как это сделать
        Например, у нас есть X/partial_sol(X) = (2, 5, 3, 10), возможные подсуммы (2, 3, 5, 7, 8, 12, 13, 15, ...), но достигнуть значений 4, 6, 9 и тд нельзя 
        Таким образом создаем prohibit[i] = хеш-таблицу, хранящую в себе недостижимые значения сумм начиная с i-го элемента
        
        На основе вышесказаного придумаем алгоритм:
        Алгоритм {
            На входе должны быть значения:
            1)Current_i - Текущая позиция
            2)Target - Искомая сумма
            3)Candidates - отсортированный в обратном порядке (начиная с больших значений) массив чисел
            4)Suffix - suffix[i] = сумма последних n - i элементов в candidates
            5)Prohibited - массив хеш-таблиц (или деревьев), хранящий значения target, недостижимых с индекса current_i
            //TODO: Как обновлять массив prohibited?
            6)nums - текущее подмножество чисел, которое возможно является частичным или полным решением, в него добавляются подходящие "кандидаты"
            
            В принципе, 3-6 можно хранить как глобальные переменные
            Итак, рассмотрим ограничения
            С1)если для текущего current_i оно выполняется, то мы добавляем это решение, + необходимо добавить все нули, которые тоже могут быть частью решения.
            C2)Решается просто, игнорируются первые k элементы, которые > target, поиск начинаем с первого candidates[current_i] <= target
            C3)По сути, проблема дублирования
            Допустим у нас 333322200 и target = 7
            Тогда решение: ^   ^^ !!
            Мы остановились на значении 2 (6-я позиция), решение (3, 2, 2), делаем шаг назад, получаем частичное решение (3, 2), потом снова возьмет снова (3, 2, 2)
            решение в таком случае следующее - каждое следующее x может только 1 раз принять значение какого-то числа (но только в своей ветке дерева обхода)
            C4)Если suffix[current_i] < target, то прекращаем для текущего частичного решения поиск для i > current_i (Тупиковая ситуация)
            C5)Если target есть в prohibited[current_i], то пропускаем этот вариант. В случае, если current_i = end, то решение не найдено, для каждого отката добавляем в prohibited[current_i] значение target
        }
        */