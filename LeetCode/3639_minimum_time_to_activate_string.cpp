#include <vector>
#include <string>

class Solution {
public:
    int minTime(std::string s, std::vector<int>& order, int k) {
        /*
        нужно найти минимальное время t, при котором количество активных подстрок (таких, что содержат как минимум 1 *) active_count >= k

        Тут тоже явно нужно использовать дерево отрезков
        //TODO: похожая задача была на Tinkoff
        //TODO: Охуеть, задача на 2-ный поиск
        Суть в чём, создаём 2 массива - L - это граница для звезды справа (когда мы ищем её границы слева)
        R - граница для звезды слева (ищем для подстрок границы справа)
        Ставим * и справа и в точке от звездочки ставим R[j] = orders[i] (k > j >= orders[i], где L[k] >= 0)
        L[j] = orders[i] (orders[i] >= j > k, где R[k] >= 0)
        L[orders[i]] = i;
        R[orders[i]] = i;

        
        */
        for (int t = 0; t < static_cast<int>(order.size()); ++t) {
            //TODO:
        }
        return -1;
    }
};