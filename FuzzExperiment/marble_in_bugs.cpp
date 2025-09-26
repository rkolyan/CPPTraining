#include <vector>
#include <climits>
#include <random>
#include <iostream>

class Solution1 {
public:
    long long putMarbles(std::vector<int>& weights, int k) {
        /*
        Итак, попробуем решить рекурсивно:
        f(A = [a1, ..., an], n, k) ->
            Если k = 1, то
                либо weight = a1 + an
		Вернуть (weight, weight)
            Иначе
                для каждого t от 1 до n-(k-1)
                    либо weight1 = weight2 = a1 + at
                    (weight1, weight2) += f([at, ... ], n - t, k - 1)
		    min_weight = min(min_weight, weight1)
		    max_weight = max(max_weight, weight2)
		Вернуть (min_weight, max_weight)

	Итак, попробуем решить задачу жадно,
	Итак, рассмотрим пример [1, 4, 2, 5, 2] 3
	Итак, сводим задачу к следующей жадной:
	Есть есть n элементов и k рюкзаков
	Выяснилось что при смещениии левой границы в случае
	[..., a_k-1, a_k],[a_k+1,...] -> [..., a_k-1],[a_k, a_k+1, ...]
	вся сумма (на всем отрезке) меняется на a_k-1 - a_k+1
	Таким образом мы просто двигаем границы до максимальных значений
	Алгоритм
	1)Расскладываем первые n-k+1 элементов в 1-й интервал, остальным элементам оставшиеся k-1 элементы выделяем
	2)Берём индекс нижней границы down = 0
	(Типа a0, a1, ... a_t])
	sum = 0
	Для (up = n - k; up < n; up++)
		sum += a[down] + a[up];
		max_up = up;
		max_a = a[up - 1] - a[up + 1];
		Для (up1 = up; up1 > down; up1--)
		[a0, a1],[a2, ...]
		dS[0] = -a2 + a1 - a1 + a0 = -a0 - a2
		dS[up-1]=
        */
	//TODO: Проверь на правильность ручками
	/*
	Почему-то неправильно работает на примере:
	weights = [54,6,34,66,63,52,39,62,46,75,28,65,18,37,18,13,33,69,19,40,13,10,43,61,72]
	k = 4

	Я попытался решить задачу LeetCode 2551 на C++. Но мой алгоритм ошибается на следующих вводных данных:
25 4
54 6 34 66 63 52 39 62 46 75 28 65 18 37 18 13 33 69 19 40 13 10 43 61 72
У меня получается 203, а должно быть 289
	*/
	int max_down = 0, max_up = 0, min_down = 0, min_up = 0;
	long long max_sum, min_sum, max_delta, min_delta, delta;
	const int n = weights.size();
	max_sum = weights[0];
	min_sum = weights[0];
	for (int up = n - k; up < n - 1; up++) {
        delta = weights[up] + weights[up + 1]; 
		max_delta = delta;
        min_delta = delta;
		max_up = up;
		min_up = up;
		for (int up1 = up - 1; up1 >= max_down; up1--) {
            delta = weights[up1] + weights[up1 + 1];
			if (delta > max_delta) {
				max_up = up1;
				max_delta = delta;
			}
		}
		for (int up2 = up - 1; up2 >= min_down; up2--) {
			delta = weights[up2] + weights[up2 + 1];
			if (delta < min_delta) {
				min_up = up2;
				min_delta = delta;
			}
		}
        max_sum += max_delta;
        min_sum += min_delta;
		min_down = min_up + 1;
		max_down = max_up + 1;
	}
	max_sum += weights[n-1];
	min_sum += weights[n-1];
	return max_sum - min_sum;
    }
};

class Solution2 {
public:
    long long putMarbles(std::vector<int>& weights, int k) {
        /*
        Сразу напрашивается на динамическое программирование
        Надо как-то разделить на k рюкзаков
        Варианты, что можно использовать

        1)строим таблицу, с максимальным расстоянием n - k
        2)по этой таблице (это получается будет матрица смежности) находим путь длиной k и максимальным весом
        3)Наверное для поиска этого пути понадобится алгоритм дейкстры
        4)аналогично, находим с минимальным весом
        5)Тут не очень понятно, а элементы вне рюкзаков должны остаться?

        [1, 5, 3, 2, 6]
        k = 3
        1->1 - 1
        1->2 - 6
        1->3 - 4
        (больше нельзя)
        2->2 - 5
        2->3 - 8
        2->4 - 7
        (больше нельзя)
        3->3 - 3
        3->4 - 5
        3->5 - 9
        (больше нельзя)
        4->4 - 2
        4->5 - 8
        (больше нельзя)
        5->5 - 6

        Либо опять же, берём dp со значениями dp[0] = 0
        dp[x] - просматриваем предыдущие суммы
        Нужно найти минимальную dp[x] и максимальную dp[x]
        Тут какие-то дополнительные структуры нужны для задачи
        Итак, попробуем решить рекурсивно:
        f(A = [a1, ..., an], n, k) ->
            Если k = 1, то
                либо weight = a1 + an
		Вернуть (weight, weight)
            Иначе
                для каждого t от 1 до n-(k-1)
                    либо weight1 = weight2 = a1 + at
                    (weight1, weight2) += f([at, ... ], n - t, k - 1)
		    min_weight = min(min_weight, weight1)
		    max_weight = max(max_weight, weight2)
		Вернуть (min_weight, max_weight)
	
        Алгоритм составили, теперь надо бы составить dp на основе этого рекурсивного алгоритма
        На первом слое рассматриваем первые элементы с 0го по n - k - 1 включительно
        5
        3 рюкзака
        5 - 3,1,1
        7 3 - 5,1,1 
        Строим таблицу префиксов
        prefix[n][n], где prefix[i][j] = {a[i] + a[j], j > i, a[i], i = j, 0 иначе

        dp[0][n] (Вычисляем значения от 0 до n - k включительно, записываем prefix[0][i])
        dp[1][n] (Далее вычисляем i от 1 до n - k + 1 включительно, для каждого j < i dp[0][j] + prefix[j + 1][i])
        dp[t][i] для i от t до n - k + t для j от t - 1 до i-1 dp[t][i] = dp[t-1][j] + prefix[j+1][i]
        
        последний (k - 1) мы проверяем только для последнего значения (то есть только n-1 для j от k-1 до n-2 dp[k-1][n-1] = dp[k-2][j] + prefix[j+1][n-1])
        Получается сложность O(k*n^2/2)
        Теперь надо бы реализовать эту херь
        [1, 4, 2, 5, 2] k=3
        [1] [4],[2,5,2] = 2 + 8 + 4 = 14
        [1] [4, 2],[5,2] = 2 + 6 + 7 = 15
        [1] [4,2,5],[2] = 2 + 9 + 4 = 15
        [1,4][2][5,2] = 5 + 4 + 7 = 16
        [1,4][2,5][2] = 16
        [1,4,2][5][2] = 3 + 10 + 4 = 17
        */
        //TODO: На литкоде даже этот вариант не проходит по времени
        //TODO: Нужно придумать жадный вариант
        //Теперь создаём два вектора dp
        std::vector<std::pair<long long, long long>> curr_dp, next_dp;
        curr_dp.resize(weights.size());
        next_dp.resize(weights.size());
        //Сначала заполняем curr_dp
        for (int i = 0; i <= weights.size() - k; ++i) {
            curr_dp[i].first = curr_dp[i].second = weights[0] + weights[i];
        }
        for (int t = 1; t < k - 1; ++t) {
            std::fill(next_dp.begin(), next_dp.end(), std::pair{INT_MAX, INT_MIN});
            for (int i = t; i <= weights.size() - k + t; ++i) {
                for (int j = t - 1; j < i; ++j) {
                    next_dp[i].first = std::min(curr_dp[j].first + weights[j+1] + weights[i], next_dp[i].first);
                    next_dp[i].second = std::max(curr_dp[j].second + weights[j+1] + weights[i], next_dp[i].second);
                }
            }
            std::swap(curr_dp, next_dp);
        }
        if (k > 1) {
            next_dp[weights.size() - 1] = std::pair{INT_MAX, INT_MIN};
            for (int j = k - 2; j < weights.size() - 1; j++) {
                next_dp[weights.size() - 1].first = std::min(curr_dp[j].first + weights[j+1] + weights[weights.size() - 1], next_dp[weights.size() - 1].first);
                next_dp[weights.size() - 1].second = std::max(curr_dp[j].second + weights[j+1] + weights[weights.size() - 1], next_dp[weights.size() - 1].second);
            }
            std::swap(curr_dp, next_dp);
        }
        return curr_dp[weights.size() - 1].second - curr_dp[weights.size() - 1].first;
    }
};

std::vector<int> generateVector(unsigned int N) {
    std::vector<int> vec;
    vec.reserve(N);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 116);

    for (unsigned int i = 0; i < N; i++) {
        vec.push_back(dist(mt));
    }
    return vec;
}

#define ELEMENTS_COUNT 20

int main(void) {
    std::vector<int> test_nums;
    Solution1 greedy;
    Solution2 dp;
    long long result1, result2;
    for (unsigned int i = 0; i < 100; i++) {
        test_nums = generateVector(ELEMENTS_COUNT);
        for (unsigned int k = 1; k <= ELEMENTS_COUNT; k++) {
            result1 = greedy.putMarbles(test_nums, k);
            result2 = dp.putMarbles(test_nums, k);
            if (result1 != result2) {
                std::cout << "Array:" << std::endl;
                for (const auto &element : test_nums) {
                    std::cout << element << ' ';
                }
                std::cout << std::endl;
                std::cout << k << std::endl;
                std::cout << "Greedy Result:" << result1 << std::endl;
                std::cout << "DP Result:" << result2 << std::endl;
            }
        }
    }
}