#include <string>
#include <vector>

/*
Итак, из-за того, что Алиса иногда с задержкой зажимает клавишу, она пишет много букв одинаковых подряд, например heeellloo
Задача, найти количество возможных строк, которое Алиса могла напечатать изначала
Итак, я так понял, что k в любом случае меньше длины строки и  
*/

//TODO: Доделать (или я уже доделал...)
class Solution {
public:
    int possibleStringCount(std::string word, int k) {
        std::vector<int> counts;
        std::vector<int> prefixes;
        std::string::value_type prev_sym = word[0];
        int sym_add_count = 0, accum = 0;
        counts.reserve(word.size());
        for (int i = 1; i < word.size(); ++i) {
            if (prev_sym != word[i]) {
                counts.push_back(sym_add_count);
                prev_sym = word[i];
                sym_add_count = 0;
            } else {
                ++sym_add_count;
            }
        }
        prefixes.reserve(counts.size());
        prefixes.push_back(0);
        for (int i = 1; i < counts.size(); ++i) {
            prefixes.push_back(counts[i-1]+prefixes.back());
        }
        /*
        1)записываем количество символов в отдельный массив counts
        Тогда минимальная длина строки = counts.size() + d = k
        d = k - counts.size();

        */
        
    }
};