#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

//SUCCESS, но очень медленный результат, скорее всего из-за того, что надо хешировать сообщения, можно было использовать таблицу [26][26] символов, ну и похуй
class Solution {
    private:
        typedef int index_t;
    public:
        int longestPalindrome(std::vector<std::string>& words) {            
            /*
            Дан массив состоящих из 2-хсимвольных строк в нижнем регистре
            Нужно найти максимальную длину палиндрома, который можно из этих слов составить
            Крайние случаи - некоторые строки могут содержать 2 одинаковых символа
            Первое что пришло в голову:
            Ищем пары палиндромов в массиве и удаляем их из words
            Одновременно с этим прибавляем к размеру 4
            После того, как все пары удалены, ищем строку с одинаковыми символами, пару с ней составить нельзя, поэтому можем вставить только 1
            Всё, профит
            Для ускорения поиска пар создаём хеш-таблицу с поиском по значению и ключом = индексу, если найдется, то удаляем её из хеш-таблицы
            */
            std::unordered_multimap<std::string, index_t> table(words.size());
            std::vector<bool> marks(words.size(), false);
            int len = 0;
            for (index_t i = words.size()-1; i >= 0; --i) {
                const auto &word = words[i];
                auto iter = table.find(word);
                if (iter != table.cend()) {
                    len += 4;
                    marks[i] = true;
                    marks[(*iter).second] = true;
                    table.erase(iter);
                } else {
                    table.emplace(std::string{word[1], word[0]}, i);
                }
            }
            for (index_t i = words.size()-1; i >= 0; --i) {
                if (!marks[i]) {
                    const auto &word = words[i];
                    if (word[0] == word[1]) {
                        len += 2;
                        break;
                    }
                }
            }
            return len;
        }
    };
int main(void) {
    std::vector<std::string> words1 = {"lc","cl","gg"}, words2 = {"ab","ty","yt","lc","cl","ab"}, words3 = {"cc","ll","xx"},words4 = {"lc","cl","aa", "gg", "aa"}, words5 = {"qo","fo","fq","qf","fo","ff","qq","qf","of","of","oo","of","of","qf","qf","of"};
    Solution sol;
    std::cout << sol.longestPalindrome(words1) << std::endl;
    std::cout << sol.longestPalindrome(words2) << std::endl;
    std::cout << sol.longestPalindrome(words3) << std::endl;
    std::cout << sol.longestPalindrome(words4) << std::endl;
    std::cout << sol.longestPalindrome(words5) << std::endl;
}