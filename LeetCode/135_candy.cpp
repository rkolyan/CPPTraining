#include <vector>
#include <queue>
#include <iostream>

//SUCCESS, но по скорости алгоритм победил только 8% людей, там можно было бы обойтись и без очереди приоритетов, используя 2 массива с префиксами, ну и ладно

class Solution {
    typedef int rating_t;
    typedef int index_t;
    using info_t = std::pair<rating_t, index_t>;
    public:
        int candy(std::vector<int>& ratings) {
            /*
            Итак, у нас n детей с рейтингами
            Каждый ребёнок имеет как минимум 1 конфету
            Дети с более высоким рейтингом получают больше конфет чем их соседи
            Нужно найти минимальное количество конфет которое нужно, чтобы распределить конфеты между детьми
            
            Ну, в голове сразу возникла мысль импользовать очередь приоритетов, в которую сохраняем пары std::pair<rating_t, index_t>
            Значения сортируем по значению рейтинга по возрастанию
            Далее, пока очередь не пуста, достаём рейтинг и индекс, если соседние рейтинги <= текущему, то просто записываем 1, иначе, берём максимальное
            значение от конфет справа и слева и записываем его + 1
            */
            const auto &N = ratings.size();
            std::vector<int> candies(N, 0);
            std::priority_queue<info_t, std::vector<info_t>, std::greater<info_t>> queue = [&]{
                std::vector<info_t> buffer;
                buffer.reserve(N);
                return std::priority_queue<info_t, std::vector<info_t>, std::greater<info_t>>(std::greater<info_t>{}, std::move(buffer));
            }();
            rating_t curr_rating;
            index_t curr_index;
            int max_candy = 0, result = 0;
            for (index_t i = 0; i < N; ++i) {
                queue.emplace(ratings[i], i);
            }
            while (!queue.empty()) {
                {
                    const auto &pair = queue.top();
                    curr_rating = pair.first;
                    curr_index = pair.second;
                    queue.pop();
                }
                max_candy = 0;
                if (curr_index > 0 && ratings[curr_index - 1] < curr_rating) {
                    max_candy = candies[curr_index - 1];
                }
                if (curr_index < N - 1 && ratings[curr_index + 1] < curr_rating) {
                    max_candy = std::max(max_candy, candies[curr_index + 1]);
                }
                max_candy++;
                candies[curr_index] = max_candy;
                result += max_candy;
            }
            return result;
        }
    };

int main(void) {
    std::vector<int> ratings1 = {1,0,2}, ratings2 = {1,2,2};
    Solution sol;
    std::cout << sol.candy(ratings1) << std::endl;
    std::cout << sol.candy(ratings2) << std::endl;
    return 0;
}