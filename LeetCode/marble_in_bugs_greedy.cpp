#include <iostream>
#include <vector>
#include <algorithm>

//SUCCESS

class Solution {
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

	Решение - там нужно просто взять k-1 наибольших соседних пар (я вроде тоже самое по логике сделал, но у меня работает неправильно(((()))))
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

class SolutionRIght {
public:
    long long putMarbles(std::vector<int>& weights, int k) {
        std::vector<int> pair_sums;
		long long diff = 0;
        pair_sums.reserve(weights.size() - 1);
        for (unsigned int i = 0; i < weights.size()-1; i++) {
            pair_sums.push_back(weights[i] + weights[i+1]);
        }
        std::sort(pair_sums.begin(), pair_sums.end());
		for (unsigned int i = 1; i < k; i++) {
			diff += pair_sums[pair_sums.size() - i] - pair_sums[i-1];
		}
		return diff;
    }
};
int main() {
    unsigned int N = 0;
    int k = 0;
    std::vector<int> a;

    std::cin >> N >> k;
    a.resize(N);
    for (auto &element : a) {
        std::cin >> element;
    }
    std::cout << SolutionRIght().putMarbles(a, k) << std::endl;
}
