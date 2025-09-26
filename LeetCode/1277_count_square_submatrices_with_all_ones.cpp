#include <vector>

//SUCCESS, 8 ms, но побеждает 44.53%, есть решение которое 0 ms, КОТОРОЕ ВЫГЛЯДИТ ТАКЖЕ КАК МОЁ, только вместо конструктора копирования там автор сам заполняет dp изначально

class Solution {
public:
    int countSquares(std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> dp(matrix);
        int count = 0;

        for (int i = 1; i < matrix.size();++i) {
            for (int j = 1; j < matrix[j].size(); ++j) {
                if (matrix[i][j]) {
                    dp[i][j] = std::min(std::min(dp[i-1][j], dp[i-1][j-1]), dp[i][j-1]) + 1;
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        for (const auto &sub_dp : dp) {
            for (const auto &element : sub_dp) {
                count += element;
            }
        }
        return count;
    }
};