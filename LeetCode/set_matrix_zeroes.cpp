#include <vector>
#include <iostream>

//SUCCESS, пространственная сложность O(1)

class Solution {
    public:
        void setZeroes(std::vector<std::vector<int>>& matrix) {
            bool zero1_fill = false, zero2_fill = false;
            const auto &N = matrix.size(), &M = matrix[0].size();
            for (const auto &element : matrix[0]) {
                if (!element) {
                    zero1_fill = true;
                    break;
                }
            }
            for (int i = 1; i < matrix.size(); i++)
            {
                auto &row1 = matrix[i-1];
                auto &row2 = matrix[i];
                zero2_fill = false;
                for (int j = 0; j < M; ++j) {
                    if (!row2[j]) {
                        zero2_fill = true;
                        for (int k = i - 1; k >= 0; --k) {
                            matrix[k][j] = 0;
                        }
                    }
                    if (!row1[j]) {
                        row2[j] = 0;
                    }
                }
                if (zero1_fill) {
                    std::fill(row1.begin(), row1.end(), 0);
                }
                zero1_fill = zero2_fill;
            }
            if (zero1_fill) {
                std::fill(matrix.back().begin(), matrix.back().end(), 0);
            }
        }
    };

void print_matrix(const std::vector<std::vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (const auto &element : row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(void) {
    std::vector<std::vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}}, matrix2 = {{0,1,2,0}, {3,4,5,2},{1,3,1,5}}, matrix3 = {{1, 2, 3, 4}, {5, 6, 7, 0}, {9, 0, 11, 12}, {13, 14, 15, 16}};
    Solution sol;
    sol.setZeroes(matrix1);
    print_matrix(matrix1);
    sol.setZeroes(matrix2);
    print_matrix(matrix2);
    sol.setZeroes(matrix3);
    print_matrix(matrix3);
    return 0;
}