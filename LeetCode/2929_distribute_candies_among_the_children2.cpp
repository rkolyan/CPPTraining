#include <iostream>
#include <vector>

//SUCCESS, но тут я не использовал формулы об общем подсчете количества таких комбинаций x + y + z = n, потому что ААААААААААААА, поэтому результат получился медленный

class Solution {
    public:
        long long distributeCandies(int n, int limit) {
            /*
            Наивный вариант (не пройдет по скорости, буду думать)
            Это использовать 2-й цикл
            for (int t = max(n - 2*limit, 0); t <= min(limit, n); ++t) {
                Каждый следующий элемент должен быть >= предыдущему
                k = n - t
                просматриваем границы k
                k1 = n - min(limit, n);
                k2 = min(2 * limit, n);
                Если k1 <= k <= k2, то всё норм

                Нужно разбить k на r1 + r2
                Если k == 2t - то всего 1 тройка (t, t, t)
                Если k == t + r или k == r + r, где r в [t1, t2], то для таких пар всего 3 троек (t, r, r), (r, t, r), (r, r, t)
                Иначе, для остальных вариантов всего (a, b, c), (b, c, a), (c, a, b), (b, a, c), (a, c, b), (c, b, a) - 6 вариантов
                Таким образом задача сводятся к следующем
                Сколько вариантов существет, чтоб разбить сумму k?
                k = r1 + r2
                r1 <= limit
                k - r1 <= limit

                r1 >= k - limit
                r1 in [k - limit, limit], вернее в [max(k - limit, 0), min(n, limit)]
                С учетом повторений сочетаний, r1 <= k / 2 + k % 2, то есть r1 in [max(k - limit, 0), min(n, limit, k / 2 + k % 2)]
                r_down = std::max(k - limit, 0);
                r_up = std::min(n, limit, k / 2 + k % 2)
                таким образом количество сочетаний c_count = max(0, r_up - r_down + 1)
            }
            */
            int t1 = std::max(n - 2*limit, 0), t2 = std::min(limit, n);
            int k1 = n - std::min(limit, n), k2 = std::min(2 * limit, n);
            int k = 0, r1 = 0, r2 = 0, r = 0;
            int variants = 0;
            long long result = 0;
            for (int t = t1; t <= t2; ++t) {
                k = n - t;
                if (k >= k1 && k <= k2) {
                    r1 = std::max(t, k - limit);
                    r2 = std::min(k / 2, t2);
                    variants = std::max(0, r2 - r1 + 1);
                    r = k - t;
                    if (r >= r1 && r <= t2) {
                        variants--;
                        if (r == t) {
                            result += 1;
                        } else {
                            result += 3;
                        }
                    } 
                    r = k / 2;
                    if (r != t && r >= r1 && r <= r2 && k == 2 * r) {
                        variants--;
                        result += 3;
                    }                    
                    result += 6 * variants;
                }
            }
            return result;
        }
};

int main(void) {
    Solution sol;
    std::cout << sol.distributeCandies(5, 2) << std::endl;
    //(1, 2, 2), (2, 1, 2), (2, 2, 1) - всего 3 варианта
    std::cout << sol.distributeCandies(3, 3) << std::endl;
    //(0, 0, 3), (0, 3, 0)
    return 0;
}