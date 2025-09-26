#include <string>
#include <vector>
#include <array>

//SUCCESS, 5 ms, наверное, из-за использований ссылок и array проигрывает, а так выигрывает 96 % (А, не, выигрывает походу всех, ну да ладно)

class Solution {
    public:
        int maxSubstrings(std::string word) {
            /*
            Задача - найти максимальное количество непересекающихся подстрок, длина которых >= 4 + строка начинается и заканчивается одним и тем же символом
            
            Итак, можно использовать хеш-таблицу и ограничитель
            Так как символы только английсие буквы нижнего регистра, то просто массив индексов последних вхождений
            */
            std::array<int, 'z'-'a'+1> arr;
            int tmp_index = 0;
            int count = 0;
            int bound = -1;
            arr.fill(-1);
            for (int i = 0; i < word.size(); ++i) {
                auto &prev_index = arr[word[i] - 'a'];
                if (prev_index != -1 && prev_index > bound) {
                    if (i - prev_index >= 3) {
                        bound = i;
                        prev_index = -1;
                        ++count;
                    }
                } else {
                    prev_index = i;
                }
            }
            return count;
        }
    };

#include <iostream>

int main(void) {
    Solution sol;
    std::cout << sol.maxSubstrings("abcdeafdef") << std::endl;
    std::cout << sol.maxSubstrings("bcdaaaab") << std::endl;
    return 0;
}