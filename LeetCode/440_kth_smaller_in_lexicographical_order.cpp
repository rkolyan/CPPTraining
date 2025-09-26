#include <iostream>
#include <vector>

//SUCCESS, бъёт 100 %, хотя у меня совсем другое решение, решение авторов через очень неявное использование префиксного дерева, до которого я не догадался.
//Думаю, на больших числах моё решение явно уступит.
//Решение с editorial
/*
class Solution {
public:
    int findKthNumber(int n, int k) {
        int curr = 1;
        k--;

        while (k > 0) {
            int step = countSteps(n, curr, curr + 1);
            if (step <= k) {
                curr++;
                k -= step;
            } else {
                curr *= 10;
                k--;
            }
        }

        return curr;
    }

private:
    int countSteps(int n, long prefix1, long prefix2) {
        int steps = 0;
        while (prefix1 <= n) {
            steps += min((long)(n + 1), prefix2) - prefix1;
            prefix1 *= 10;
            prefix2 *= 10;
        }
        return steps;
    }
};
*/

//Моё решение
class Solution {
    private:
        /*
        если n = 34, то divide = 11
        */
        int createDivide(int n) {
            long divide = 1;
            while (divide <= n) {
                divide = divide * 10 + 1;
            }
            divide /= 10;
            return static_cast<int>(divide);
        }
        void fill_up_bounds(std::vector<int> &bounds_stack, int n) {
            bounds_stack.reserve(10);
            while (n > 0) {
                bounds_stack.push_back(n % 10);
                n /= 10;
            }
        }
        void fill_k_indexes_and_nums(const std::vector<int> &bounds_stack, std::vector<int> &k_indexes, std::vector<int> &nums, int k_end) {
            k_indexes.reserve(bounds_stack.size()-1);
            k_indexes.push_back(k_end + 1);
            nums.resize(bounds_stack.size()-1);
            /*
            Итак было число 1253
            Если у нас последнее число 9 -> увеличиваем
            А если б у нас было число 1299, то следующее число было бы 13
            (9,9)
            */
            int divide = 1;
            for (int i = 1; i < bounds_stack.size()-1; ++i) {
                if (bounds_stack[i] == 9) {
                    k_indexes.push_back(k_indexes.back());
                } else {
                    k_indexes.push_back(k_indexes.back() + (9 - bounds_stack[i]) * divide);
                }
                divide = divide * 10 + 1;
            }
            /*
            Итак, по идее мы создали массив позиций следующих спусков
            Теперь 
            */
            int num = 0;
            for (int i = nums.size()-1; i >=0; --i) {
                num = num * 10 + bounds_stack[i+1];
                if (bounds_stack[i+1] == 9) {
                    nums[i] = nums[i+1];
                } else {
                    nums[i] = num + 1;//TODO: Может + 1?
                }
            }
        }
        int find_k_number1(int k, int divide, int d) {
            int num = 0, delta = 0;
            while (k) {
                delta = (k-1) / divide;
                k = (k - 1) - delta * divide;
                num = num * 10 + d + delta;
                d = 0;
                divide /= 10;
            }
            return num;
        }
        int find_k_number2(int k, std::vector<int> &k_indexes, std::vector<int> &nums) {
            int divide = 1, k1 = 0, k2 = 0, num = 0, remind = 0, delta = 0;
            for (int i = 1; i < k_indexes.size(); ++i) {
                k1 = k_indexes[i-1];
                k2 = k_indexes[i];
                if (k1 <= k && k < k2) {
                    num = nums[i-1];
                    while (divide) {
                        remind = (k - k1) % divide;
                        delta = (k - k1) / divide;
                        if (remind == 0) {
                            num += delta;
                            return num;
                        } else {
                            num = (num + delta) * 10;
                            k1 += delta * divide + 1;//TODO: Может +1 не нужен?
                        }
                        divide /= 10;
                    }
                }
                divide = divide * 10 + 1;
            }
            return find_k_number1(k - k_indexes[k_indexes.size() - 1] + 1, divide, nums[nums.size()-1]);
        }
        int find_k_end(std::vector<int> &bounds_stack, int divide) {
            int k_end = 0;
            int d = 1;
            auto iter = bounds_stack.crbegin();
            while (iter != bounds_stack.crend()) {
                k_end = k_end + (*iter - d) * divide + 1;
                divide /= 10;
                ++iter;
                d = 0;
            }
            return k_end;
        }
    public:
        int findKthNumber(int n, int k) {
            std::vector<int> bounds_stack;
            int k_end = 0;
            fill_up_bounds(bounds_stack, n);
            int divide = createDivide(n);
            k_end = find_k_end(bounds_stack, divide);
            if (k_end > k) {
                return find_k_number1(k, divide, 1);
            } else if (k_end < k) {
                std::vector<int> k_indexes, nums;
                fill_k_indexes_and_nums(bounds_stack, k_indexes, nums, k_end);
                return find_k_number2(k, k_indexes, nums);
            }
            return n;
            /*
            Итак алгоритм следующий
            1)вычисляем k_end - значение, до которого мы можем спокойно использовать первую задачу
            Для этого:
                разложить число на сумму степеней 10 - например 1253 будет (3,5,2,1), size = 
                Далее найти максимальное число p = sum(10^r) для r от 0 до ... короче максимальное p <= 1253
                Далее k_end = (1-1) * 1111 + 1 = 1 (потому что 1,10,100,1000)
                Далее k_end = 1 + (2-0) * 111 + 1 = 224
                      k_end = 224 + (5-0)*11 + 1 = 225+ 55 = 280
                      k_end = 280 + (3-0)*1 + 1 = 284
                Алгоритм вычисления k_end:
                k_end = 0;
                d = 1;
                while (p) {
                    k_end = k_end + (stack.back() - d) * p + 1;
                    p /= 10;
                    stack.pop();
                    d = 0;
                }
            2)Если k < k_end
            divide - это p
            int num = 0, delta = 0, d = 1;
            while (k) {
                delta = (k-1) / divide;
                k = (k - 1) - delta * divide;
                num = num * 10 + d + delta;
                d = 0;
                divide /= 10;
            }
            3)Если k > k_end
            тогда divide = p / 10
            Ищем на основе стека (в нашем случае 3,5,2,1) позиции k1,k2,k3
            k0 = k_end
            k1 = k0 + 1     126
            k2 = k1 + (9 - 6 + 1) * 1 = k1 + 4 ---> 127,128,129,13
            k3 = k2 + (9 - 3 + 1) * 11 = k2 + 77 ---> 130...139,14,140...149,15....,19,190,...,199, 2
            Храним полуитнервалы
            текущий num = 126
            Если k1 <= k и k < k2:
                Например k = k1 + 2, тогда  num 126,127,128,129],13
                но num = num + 2;
            Иначе если k2 <= k и k < k3:
                Например k = k2 + 22, тогда num 13,131,132,133,134,135,136,137,138,139,14,140,141,142,143,144,145,146,147,148,149,15 - num должно быть 15
                если (k - k2) % 11 == 0, то последний элемент увеличиваем на (k-k2)/11
                Например k = k2 + 21,
                если (k - k2) % 11 == h > 0, то увеличиваем последний разряд на (k - k2) / 11
                k_begin = k2 + ((k-k2)/11)*11
                добавляем разряд 0
                (k - k_begin) % 1 == 0, увеличиваем последний разряд на (k - k_begin)/1
            Иначе, если k >= k3
                k - k3 % 111 == 0 - увеличиваем последний разряд на (k - k3)
            
            Тогда текущий алгоритм получается следующий
            divide = 1;
            for (int i = 1; i < k_vector.size(); ++i) {
                k1 = k_vector[i-1];
                k2 = k_vector[i];
                if (k1 <= k && k < k2) {
                    num = nums[i-1];
                    while (divide) {
                        remind = (k - k1) % divide;
                        delta = (k - k1) / divide;
                        if (remind == 0) {
                            num += delta;
                            return num;
                        } else {
                            num = (num + delta) * 10;
                            k1 += delta * divide + 1;//TODO: Может +1 не нужен?
                        }
                        divide /= 10;
                    }
                }
                divide = divide * 10 + 1;
            }
            d = nums[nums.size()-1]
            //А дальше функция аналогичная 2)
            */
        }
    };

int main(void) {
    Solution sol;
    /*
    std::cout << sol.findKthNumber(1000000000, 1000000000) << std::endl;
    std::cout << sol.findKthNumber(1253, 981) << std::endl;//753
    std::cout << sol.findKthNumber(1253, 286) << std::endl;//127
    std::cout << sol.findKthNumber(1253, 289) << std::endl;//13
    std::cout << sol.findKthNumber(1253, 301) << std::endl;//140
    std::cout << sol.findKthNumber(1253, 365) << std::endl;//199
    std::cout << sol.findKthNumber(1, 1) << std::endl;
    */
    std::cout << sol.findKthNumber(10, 2) << std::endl;
    return 0;
}