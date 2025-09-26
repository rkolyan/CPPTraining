
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//SUCCESS, но время выполнения 192 ms, хотя у меня вроде алгоритм тот же самый, что и у гениев оптимизации...

class Solution {
    private:
        #define MOD 1000000007
        long binpow(long a, long b) {
            long res = 1;
            while (b > 0) {
                if (b & 1) {
                    res = (res * a) % MOD;
                }
                a = (a * a) % MOD;
                b >>= 1;
            }
            return res;
        }
        long findCombination(int t, int n) {
            if (t < 0 || t > n) {
                return 0;
            }
            std::vector<long> fact, inv_fact;
            fact.reserve(n+1);
            inv_fact.resize(n+1);
            fact.push_back(1);
            for (int i = 1; i <= n; ++i) {
                fact.push_back((fact.back() * i) % MOD);
            }
            inv_fact[n] = binpow(fact[n], MOD-2);
            for (int i = n - 1; i >= 0; --i) {
                inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
            }
            return (((fact[n] * inv_fact[t]) % MOD) * inv_fact[n - t]) % MOD;
        }
        long oldFindCombination(int t, int n) {
            if (n == 0) {
                return 1;
            }
            std::vector<long> combinations;
            combinations.reserve(n+1);
            combinations.push_back(1);
            combinations.push_back(1);
            for (int i = 2; i <= n; ++i) {
                for (int j = combinations.size()-1; j > 0; --j) {
                    combinations[j] = (combinations[j] + combinations[j-1]) % MOD;
                }
                combinations.push_back(1);
            }
            return combinations[t];
        }
        long findMultiplication(int n, int m, int t) {
            long result = m;
            long m_1 = m - 1;
            for (int i = n - 1 - t; i > 0; --i) {
                result = (result * m_1) % MOD; 
            }
            return result;
        }
    public:
        int countGoodArrays(int n, int m, int k) {
            /*
            Нужно найти C^{k}_{n-1}
            dp[t] = m * (m-1)^(n-1-t) * C^t_{n-1}
            */
            return static_cast<int>((findMultiplication(n, m, k) * findCombination(k, n-1)) % MOD);
        }
        int oldCountGoodArrays(int n, int m, int k) {
            std::vector<long int> dp0(k + 1, 0), dp1(k + 1, 0);
            int m_1 = m - 1;
            dp1[0] = m;
            for (int i = 1; i <= k; ++i) {
                dp0[0] = (dp1[0] * m_1) % MOD;
                for (int t = 1; t <= i; ++t) {
                    dp0[t] = (dp1[t] * m_1 + dp1[t-1]) % MOD;
                }
                std::swap(dp0, dp1);
            }

            for (int i = k + 1; i < n; ++i) {
                dp0[0] = (dp1[0] * m_1) % MOD;
                for (int t = 1; t <= k; ++t) {
                    dp0[t] = (dp1[t] * m_1 + dp1[t-1]) % MOD;
                }
                std::swap(dp0, dp1);
            }
            return static_cast<int>(dp1[k]);
        }
        std::vector<std::string> createGoodArraysFormulas(int n, int k) {
            std::vector<std::string> dp0(k + 1, ""), dp1(k + 1, "");
            dp1[0] = "m";
            /*
            Допустим n = 3, m = 2, k = 1
            Итак, допуситм первое число l
            первое число может принимать m различных значений
            l
            dp[0] = m
            Допустим, если второе число == l
            */
            for (int i = 1; i <= k; ++i) {
                if (dp1[0] != "") {
                    dp0[0] = "(" + dp1[0] + "*(m-1))";
                } else {
                    dp0[0] = "m";
                }
                for (int t = 1; t <= i; ++t) {
                    if (dp1[t] != "") {
                        dp0[t] = "(" + dp1[t] + "*(m-1) + " + dp1[t-1] + ")";
                    } else {
                        dp0[t] = dp1[t-1];
                    }
                }
                std::swap(dp0, dp1);
            }

            for (int i = k + 1; i < n; ++i) {
                dp0[0] = "(" + dp1[0] + "*(m-1))";
                for (int t = 1; t <= k; ++t) {
                    dp0[t] = "(" + dp1[t] + "*(m-1) + " + dp1[t-1] + ")";
                }
                std::swap(dp0, dp1);
            }
            return dp1;
        }


        #define _FILE_OUTPUT

        void printFormulas(const std::vector<std::string> &formulas) {
            #ifdef _FILE_OUTPUT
            std::ofstream outFile("tmp.txt");
            #endif
            for (int i = 0; i < formulas.size(); ++i) {
                #ifdef _FILE_OUTPUT
                outFile << i << "\t:\t" << formulas[i] << std::endl;
                #else
                std::cout << i << "\t:\t" << formulas[i] << std::endl;
                #endif
            }
        }
    };

#include <iostream>
int main(void) {
    Solution sol;
    /*
    std::cout << sol.countGoodArrays(3,2,1) << std::endl;
    std::cout << sol.countGoodArrays(4,2,2) << std::endl;
    std::cout << sol.countGoodArrays(5,2,0) << std::endl;
    std::cout << sol.countGoodArrays(3,3,0) << std::endl;
    */
    std::cout << sol.countGoodArrays(42367,39220,7691) << std::endl;
    /*
    std::vector<std::string> formula;
    formula = sol.createGoodArraysFormulas(6, 5);
    sol.printFormulas(formula);
    */
    return 0;
}
/*
0	:	((((m*(m-1))*(m-1))*(m-1))*(m-1))
1	:	(((m*(m-1) + (m*(m-1)))*(m-1) + ((m*(m-1))*(m-1)))*(m-1) + (((m*(m-1))*(m-1))*(m-1)))
2	:	((m*(m-1) + (m*(m-1) + (m*(m-1))))*(m-1) + ((m*(m-1) + (m*(m-1)))*(m-1) + ((m*(m-1))*(m-1))))
3	:	(m*(m-1) + (m*(m-1) + (m*(m-1) + (m*(m-1)))))
4	:	m

n = 5
k = 5

dp[0] = m * (m-1)^4
dp[1] = 4m*(m-1)^3
dp[2] = 6m*(m-1)^2
dp[3] = 4m*(m-1)^1
dp[4] = m

Моё предположение dp[t] = m * (m-1)^(n-1-t) * C^t_{n-1} (сочетание из n-1 по t)
Свойства сочетания
C^{k}_{n} = C^{k-1}_{n-1} + C^{k}_{n-1}
C^{0}_{1} = C^{1}_{1} = 1
C^{0}_{2} = 1

*/