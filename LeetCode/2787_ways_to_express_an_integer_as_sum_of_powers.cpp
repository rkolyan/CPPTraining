#include <vector>

/*
Ну, вроде не сложная задача задача
представим dp[num] - как количество возможных вариантов сумм чисел (n_i)^x
Тогда для начала нам нужно вычислить dp[num-(n_i)^x]
Также тут нужно учитывать формулу включения и исключения, таким образом
возможных вариантов предстваления числа = dp[num-(n_i)^x] + dp[num-(n_j)^x] - dp[num - ((n_i)^x+(n_j)^x)]
*/

#define MODULO 1000000007

//SUCCESS, 17 ms, побеждает 89,76 %
/*
Вот самое быстрое решение за 6 ms:

long long dp[301][301][6] = {};
class Solution {
public:
long long dfs(int i, int n, int x) {
    if (pow(i, x) > n)
        return n == 0;
    if (dp[i][n][x] == 0)
        dp[i][n][x] = 1 + dfs(i + 1, n - pow(i, x), x) + dfs(i + 1, n, x);
    return dp[i][n][x] - 1;
}
int numberOfWays(int n, int x) {
    return dfs(1, n, x) % 1000000007;
}
};
*/
class Solution {
public:
    int numberOfWays(int n, int x) {
        std::vector<int> powers;
        powers.reserve(300);
        for (long num = 1, tmp_num = 1; num <= 300; ++num, tmp_num = 1) {
            for (int power = 0; power < x; ++power) {
                tmp_num *= num;
                if (tmp_num > n) {
                    goto POWERS_END;
                }
            }
            powers.push_back(static_cast<int>(tmp_num));
        }
    POWERS_END:
        std::vector<long> dp(n+1, 0);
        dp[0] = 1;
        int next_num = 0;
        for (const auto &num : powers) {
            for (int prev_num = n - num; prev_num >= 0; --prev_num) {
                next_num = prev_num + num;
                dp[next_num] = (dp[next_num] + dp[prev_num]) % MODULO;
            }
        }
        return dp[n];
    }
};

//Опять я недочитал, там нужно чтоб каждое слагаемое было уникальным
class Solution1 {
public:
    int numberOfWays(int n, int x) {
        std::vector<int> powers;
        powers.reserve(300);
        for (long num = 1, tmp_num = 1; num <= 300; ++num, tmp_num = 1) {
            for (int power = 0; power < x; ++power) {
                tmp_num *= num;
                if (tmp_num > n) {
                    goto POWERS_END;
                }
            }
            powers.push_back(static_cast<int>(tmp_num));
        }
    POWERS_END:
        std::vector<long> dp(n+1, 0);
        dp[0] = 1;
        int power_max_index = 0, prev_num = 0;
        for (int num = 1; num <= n; ++num) {
            if (power_max_index < static_cast<int>(powers.size())-1 && (powers[power_max_index+1] <= num)) {
                ++power_max_index;
            }
            for (int index = power_max_index; index >= 0; --index) {
                dp[num] = (dp[num] + dp[num - powers[index]]) % MODULO;
            }
            for (int index1 = 0; index1 <= power_max_index; ++index1) {
                for (int index2 = index1+1; index2 <= power_max_index; ++index2) {
                    prev_num = num - powers[index1] - powers[index2];
                    if (prev_num < 0) {
                        break;
                    }
                    dp[num] -= dp[prev_num];
                    if (dp[num] < 0) {
                        dp[num] = MODULO + dp[num];
                    }
                }
            }
        }
        return static_cast<int>(dp[n]);
    }
};

#include <iostream>

int main(void) {
    Solution sol;

    std::cout << sol.numberOfWays(9, 1) << std::endl;
    return 0;
}