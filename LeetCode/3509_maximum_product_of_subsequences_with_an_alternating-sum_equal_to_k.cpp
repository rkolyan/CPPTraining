
/*
Задача на бектрекинг
1)Нужно создать три матрицы
1)counts[i][sum] - количество таких комбинаций возможных сум чисел из nums равных sum справа начиная от i, в случае если следующий знак g = 1 - g
2)is_in[i][sum] - участвует ли nums[i] в такой комбинации или нет
3)indexes[i][sum] - хранит индексы следующих элементов участвующих в сумме

Возможно стоит обойтись без is_in, тогда поступим иначе
counts[i][sum] - количество таких комбинаций возможных сум чисел из nums равных sum справа начиная от i (сам элемент nums[i] также участвует в этой сумме)
indexes[i][sum] - хранит индексы следующих элементов участвующих в каждой отдельной сумме

Собственно первый этап - построить эти 2 таблицы
Алгоритм построения следующий
indexes[nums.size()-1][nums.back()].resize(1, nums.back());
tmp_indexes[nums.back()] = nums.size()-1;
int subsum;
for (int i = nums.size()-2; i >= 0; --i) {
    for (int sum = ; sum <= level; ++sum) {
        subsum = (nums[i] - sum + CENTER;
        if (!tmp_indexes[subsum].empty())
        tmp_indexes[subsum].push_back(i);
    }
    tmp_indexes[nums[i]].push_back(i);
}
//Короче можем использовать tmp_indexes, только надо делать +CENTER к отицательным значениям суммы

Далее, бектрекинг
Можно ли тут для ускорения использовать двоичный поиск?
Наверное нет
Блин, а зачем бектрекинг, вместо хранения индексов можно ведь сразу хранить значения произведени

Так, в принципе можно использовать только вот этот вот tmp_indexes для бектрекинга
нужно хранить промежуточные индексы
tmp_indexes[sum] - добавляет

*/

//TODO: Время выполнения((((((

/*
Итак, какую структуру данных нужно использовать для ускорения?
количество всех возможных подсум возрастает до бесконечности
Таким образом, нам надо... А что надо? 
можно сделать meet-in-the-middle через prefixные значени и суффиксные
Так, хорошо, варианты мышления
Методы от противного:
1)Ну, как-то искать сумму при вычитании других
Может найти все альтернативные суммы и засунуть их в очередь приоритетов
Как в той задаче, где мы добавляли и убирали пути

Структуры:

Ну, в топиках задачи написано, что она на дп и использование хеш-таблиц (я так и сделал...)
можно убрать sign, и вместо него сделать пару, просто обходя числа в обратном порядке.
Тогда как минимум чисел будет в 2 раза меньше



*/

#include <vector>
#include <unordered_set>
#include <tuple>
class Solution {
private:
    struct myhash {
        inline size_t operator()(const std::tuple<int, int, int> &t) const {
            std::hash<int> int_hasher;
            return int_hasher(std::get<0>(t)) ^ int_hasher(std::get<1>(t)) ^ int_hasher(std::get<2>(t));
        }
    };
public:
    int maxProduct(std::vector<int>& nums, int k, int limit) {
        constexpr int BUF_SIZE = 150 * 12 * 2;
        int tmp_product, tmp_sum, tmp_sign;
        std::unordered_set<std::tuple<int, int, int>, myhash> old_table, new_table;
        old_table.reserve(BUF_SIZE);
        new_table.reserve(BUF_SIZE);
        for (const auto &num : nums) {
            for (const auto &t : old_table) {
                new_table.insert(t);
                tmp_sign = -std::get<2>(t);
                tmp_sum = std::get<0>(t) + tmp_sign * num;
                tmp_product = std::get<1>(t);
                if (tmp_product <= limit || !num) {
                    tmp_product *= num;
                }
                new_table.emplace(tmp_sum, tmp_product, tmp_sign);
            }
            new_table.emplace(num, num, 1);
            std::swap(new_table, old_table);
        }
        int max_product = -1;
        for (int product = 0; product <= limit; ++product) {
            for (const auto &sign : {-1,1}) {
                auto iter = old_table.find({k, product, sign});
                if (iter != old_table.end()) {
                    max_product = product;
                }
            }
        }
        return max_product;
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<int> nums{10,9,9,1,7,7,0,3,7,4,11,1,4,4,6,0,0,2,9,12,6,5,9,11,9,0,1,6,6,1,2,6,9,7,3,8,5,5,12,3,9,5,6,3,11,0,10,11,5,10,5,8,10,0,3,0,3,9,3,5,12,9,9,1,6,10,1,8,10,4,9,11,6,9,12,10,8,7,5,1,9,3,2,12,9,5,8,3,7,0,5,6,10,4,12,9,10,7,10,9};
    std::cout << sol.maxProduct(nums, 1, 30) << std::endl;
}