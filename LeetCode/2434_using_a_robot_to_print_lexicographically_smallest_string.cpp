#include <iostream>
#include <vector>

//SUCCESS, 26 ms, побеждает 93 %, минимально достигнуто 20 ms, там какие-то хитровыебанные оптимизации, до которых я не догадался, потому что я думал 10 минут

class Solution {
    public:
        std::string robotWithString(std::string s) {
            /*
            Итак, робот либо:
            1)берет первый элемент из строки s и записывает его в конец t
            2)либо берёт последний элемент из строки t и записывает его в конец строки r
            Делается это, пока все символы из s не будут в r
            Найти минимальное лексикографическое r

            Итак, это задача получается похожа на Ханойскую башню, только у нас всего 2 шеста для дисков, и обратно перекладывать диски нельзя
            Попробуем рассмотреть какой-нибудь сложный пример
            fasfnomrioen
            минимально возможный (или невозможный) результат = aeffimnnoors
            Такой результат получить не возможно
            Итак, в начале s = "fasfnomrioen", t = "", r = ""
            s = "sfnomrioen", t = "fa". r = ""
            итак, мы можем в начале напечатать ae - при первом проходе, при этом s = "n" t = fsfnomrio
            таким образом, алгоритм сводится к следующему - 
            ищем минимально возможную строку, которую можно сформировать при первом проходе,
            то есть необходимо найти индексы первых k минимумов, такие, что a[i_1] <= a[i_2] <= ... <= a[i_k] - их записываем в r
            Далее, итеративно сравниваем первый элемент s и последний элемент t и берём из них наименьший
            Короче алгоритм следующий - находим все такие k индексов
            До этих элементов доходим, строя t, записываем a[i_{j}] в массив, и пока последний элемент b в t : b <= a[i_{j+1}], затем идём к следующему индексу
            Таким образом алгоритм следующий:
            Вычислим массив суффиксов строки s, в качестве суффикса будет индекс минимума ( причем минимум обновляется через условие new_min <= old_min)
            Обход делаем с конца,
            Затем проходимся в строке, пока не будет встречен следующий минимум и проверяем t
            */
            const auto N = s.size();
            std::string t, result;
            std::string::value_type cur_min;
            int min_index = 0;
            std::vector<int> prefix(N);
            t.reserve(N);
            result.reserve(N);
            cur_min = s[N-1];
            min_index = N - 1;
            prefix[N-1] = min_index;
            for (int i = N - 2; i >= 0; --i) {
                if (cur_min >= s[i]) {
                    min_index = i;
                    cur_min = s[i];
                }
                prefix[i] = min_index;
            }
            for (int i = 0; i < N; i = prefix[i] + 1) {
                for (int j = i; j < prefix[i]; ++j) {
                    t.push_back(s[j]);
                }
                result.push_back(s[prefix[i]]);
                if (prefix[i] < N - 1) {
                    cur_min = s[prefix[prefix[i]+1]];
                    while (!t.empty() && cur_min >= t.back()) {
                        result.push_back(t.back());
                        t.pop_back();
                    }
                }
            }
            while (!t.empty()) {
                result.push_back(t.back());
                t.pop_back();
            }
            return result;
        }
    };

int main(void) {
    Solution sol;
    std::cout << sol.robotWithString("fasfnomrioen") << std::endl;
    std::cout << sol.robotWithString("zza") << std::endl;
    std::cout << sol.robotWithString("bac") << std::endl;
    std::cout << sol.robotWithString("bdda") << std::endl;
}