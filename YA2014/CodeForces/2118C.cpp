#include <iostream>
#include <vector>
#include <queue>
/*
Дан массив чисел, красота каждого числа = количество 1, красота массива - сумма красот его чисел
Операция над числом - прибавление 1
Найти максимальную красоту массива после выполнения не более k операций (возможно и 0)

Итак,
если первый бит и последующие подряд идущие = 1, то они превратятся в 0 после прибавления 1
1x16 -> 1x1 и 16x0
1  2 3  4 5 6 7  8 9 10 11 12 13 14 15  16
1  1 2  1 2 2 3  1 2 2   3 2   3  3  4   1

Итак, 1)сначала добавляем в четные числа единицы -> тогда красота массива увеличится на такое количество 1
2)Далее, надо определить такое наименьшее y > x, которое красивее - логично что y = 2^t + x, где t - номер первого бита с 0-м
Короче, задача решается с очередью приоритетов, сортируем значения по t, сначала берём числа с наименьшим t, <t, a_x>

*/

typedef unsigned int bit_t;
typedef unsigned int beauty_t;
typedef unsigned long long number_t;
using queue_element_t = std::pair<bit_t, number_t>;

bit_t find_t(number_t num) {
    bit_t bit = 0;
    while (num) {
        if (!(num & 1)) {
            return bit;
        }
        ++bit;
        num >>= 1;
    }
    return bit;
}

beauty_t find_beauty(number_t num) {
    beauty_t beauty = 0;
    while (num) {
        if (num & 1) {
            ++beauty;
        }
        num >>= 1;
    }
    return beauty;
}

beauty_t find_base_beauty(const std::vector<number_t> &a) {
    beauty_t beauty = 0;
    for (const auto &num : a) {
        beauty += find_beauty(num);
    }
    return beauty;
}

beauty_t find_max_beauty(const std::vector<number_t> &a, number_t k) {
    std::priority_queue<queue_element_t, std::vector<queue_element_t>, std::greater<queue_element_t>> queue = [&]{
        std::vector<std::pair<unsigned int, unsigned long long>> buffer;
        buffer.reserve(a.size());
        return std::priority_queue<queue_element_t, std::vector<queue_element_t>, std::greater<queue_element_t>>(std::greater<queue_element_t>{}, std::move(buffer));
    }();
    beauty_t beauty = find_base_beauty(a);
    number_t delta = 0;
    std::pair<bit_t, number_t> tmp_pair;
    for (const auto &num : a) {
        queue.emplace(find_t(num), num);
    }
    //TODO: Наверное, кто будет просматривать, тот будет меня банить на интервью
    while (true) {
        tmp_pair = queue.top();
        queue.pop();
        delta = static_cast<number_t>(1) << tmp_pair.first;
        if (delta <= k) {
            ++beauty;
            k -= delta;
            tmp_pair.second += delta;
            tmp_pair.first = find_t(tmp_pair.second);
            queue.push(tmp_pair);
        } else {
            break;
        }
    }
    return beauty;
}


int main(void) {
    int t = 0;
    int n = 0;
    number_t k = 0;
    std::vector<number_t> array;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        array.resize(n);
        for (auto &element : array) {
            std::cin >> element;
        }
        std::cout << find_max_beauty(array, k) << std::endl;
    }
    return 0;
}