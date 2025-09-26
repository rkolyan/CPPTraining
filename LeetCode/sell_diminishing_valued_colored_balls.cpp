#include <vector>
#include <iostream>
#include <algorithm>
//SUCCESS, можно было бы сделать подфункцию в выражении, но мне было впадлу
#define MOD 1000000007

class Solution {
    public:
        int maxProfit(std::vector<int> &inventory, int orders) {
            /*
            Алгоритм действий
            1 - отсортировать массив
            */
            if (inventory.size() == 1) {
                long result = (static_cast<long>(orders) * (static_cast<long>(inventory[0]) + static_cast<long>(inventory[0] - orders + 1))) / 2;
                return static_cast<int>(result % MOD);
            }
            std::sort(inventory.begin(), inventory.end(), std::greater<int>{});
            long tmp = 0, prev_level = 0, next_level = inventory[0], d1 = 0, d2 = 0;
            long profit = 0, s_tmp = 0;
            for (int x = 1; orders && x < inventory.size(); ++x) {
                prev_level = next_level;
                next_level = inventory[x];
                tmp = std::min(static_cast<long>(orders), (prev_level - next_level)*x);
                d1 = tmp / x;
                s_tmp = x * (prev_level + (prev_level - d1 + 1)) * d1 / 2;
                profit = (profit + s_tmp) % MOD;
                d2 = tmp % x;
                s_tmp = d2 * (prev_level - d1);
                profit = (profit + s_tmp) % MOD;
                orders -= tmp;
            }
            prev_level = next_level;
            next_level = 0;
            int x = inventory.size();
            tmp = std::min(static_cast<long>(orders), (prev_level - next_level)*x);
            d1 = tmp / x;
            s_tmp = x * (prev_level + (prev_level - d1 + 1)) * d1 / 2;
            profit = (profit + s_tmp) % MOD;
            d2 = tmp % x;
            s_tmp = d2 * (prev_level - d1);
            profit = (profit + s_tmp) % MOD;
            return static_cast<int>(profit);
    };

    /*
    Итак, этот вариант не проходит по времени выполнения
    Тогда, для ускорения можно рассчитывать разности между предыдущим уровнем и следующим
    Например у нас есть 20 10 8 5
    В начале мы трогаем 10 раз (от 20 до 10 не включая 10) только белые шары (1 белый) - арифметическая прогрессия с b = -1
    Потом мы 2 раза трогаем белые и желтые шары (от 10 до 8) - (белый, желтый, белый, желтый) - 2 арифметические прогрессии
    Таким образом мы в начале сортируем по убыванию инвентарь
    Затем для каждого следующего уровня шара добавляем следующую арифметическую последовательность
    Пока рассмотрим ситуацию не думая о переполнении типа
    a1, a2, a3, a4
    Начинаем между a1 и a2, 
    Сумма арифметической прогресси = (a1/2 + a2/2) * (a1 - a2) (n = a1 - a2)
    В плане переполнения проблема - можно сделать (a1 - a2)^2 - тип long такое примет, затем делим 2 и делаем % MOD, потом уже прибавляем к результату
    у нас было orders количество требуемых шаров
    tmp = std::min(orders, (a1 - a2))
    Получаем s = (a1 + (a1 - tmp)) * tmp / 2
    Это в случаем когда арифметическая прогрессия только 1, но в случае если их более 1
    Пусть арифметических прогрессий x, тогда
    мы имеем orders и a_i - a_{i+1}
    tmp = std::min(orders, (a_i - a_{i+1})*x)
    Снизу выражение +1 под вопросом 
    Далее, мы делаем d1 = tmp / x и ищем суммы s1 = x * s = x * (a1 + (a1 - d1 + 1)) * d1 / 2
    и d2 = tmp % x и вычисляем s2 = d2 * (a1 - d1)
    мы делаем x сумм
    */
};

int main(void) {
    std::vector<int> inventory2 = {3, 5}, inventory1 = {2, 5}, inventory3 = {1000000000};
    Solution sol;
    std::cout << sol.maxProfit(inventory1, 4) << std::endl;
    std::cout << sol.maxProfit(inventory2, 6) << std::endl;
    std::cout << sol.maxProfit(inventory3, 1000000000) << std::endl;

    return 0;
} 