#include <vector>

//SUCCESS, 4 ms, побеждает 95.21%

/*
Вот результат за 0 ms, да... он самый быстрый... из-за арифметичемких особенностей колец вычет, про которые я забыл

class Solution {
public:
    vector<int> productQueries(int n, const vector<vector<int>>& queries) {
        constexpr int MOD = 1000000007;
        vector prefix {0};
        while (n) {
            const int j = __builtin_ctz(n);
            prefix.push_back(prefix.back() + j);
            n -= 1 << j;
        }
        n = prefix.back();
        vector ans {1}; ans.reserve(n);
        for (int i = 1; i <= n; i++)
            ans.push_back((ans.back() << 1) % MOD);
        vector<int> ret; ret.reserve(queries.size());
        for (const auto& q : queries)
            ret.push_back(ans[prefix[q[1] + 1] - prefix[q[0]]]);
        return ret;
    }
};
*/

class Solution {
    #define MODULO 1000000007
    #define DIM_SIZE (sizeof(int) * 8 - 1)
    void calculateTables(int n, int table[DIM_SIZE][DIM_SIZE]) {
        for (int i = 0, j = 0, bit = 1; i < DIM_SIZE; ++i, bit <<= 1) {
            if (bit & n) {
                table[j][0] = bit;
                for (int j1 = 1; j1 <= j; ++j1) {
                    table[j][j1] = static_cast<int>(static_cast<long>(bit) * static_cast<long>(table[j-1][j1-1]) % MODULO);
                }
                ++j;
            }
        }
    }
    std::vector<int> findProducts(int table[DIM_SIZE][DIM_SIZE], const std::vector<std::vector<int>> &queries) {
        std::vector<int> products;
        products.reserve(queries.size());
        for (const auto &query : queries) {
            products.push_back(table[query[1]][query[1]-query[0]]);
        }
        return products;
    }
public:
    std::vector<int> productQueries(int n, std::vector<std::vector<int>> &queries) {
        int mults[DIM_SIZE][DIM_SIZE];
        calculateTables(n, mults);
        return findProducts(mults, queries);
    }
};