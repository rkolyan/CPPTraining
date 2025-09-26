#include <iostream>
#include <vector>
#include <climits>

class Solution {
    public:
        int findLongestPath(const std::vector<std::vector<int>> &matrix) {
            size_t n = matrix.size(), m = matrix[0].size();
            int dp[n][m];
            int marks[n][m] = {false};
            unsigned int max_path = 1, curr_path = 1;
            for (size_t i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    dp[i][j] = 1;
                }
            }
            /*
            for (int i = 1; i < n - 1; i++) {
                for (int j = 1; j < m - 1; j++) {
                    if (dp[i][j] == 1) {
                        //1)
                        curr_path = 0;
                        //2)Помечаем, что
                        marks[i][j] = MOVE_BEGIN;
                        do {

                        } while ()
                    }
                }
            }
            */
            /*
            Создаём матрицу размера mxn, заполняем 1цами
            f(matr, i, j, n, m) {
                Если matr[i][j] > 1
                    Вернуть matr[i][j]
                просматриваем элементы индекса на позициях (i+1,j),(i-1,j),(i,j-1),(i,j+1),
                если элементы на этих позициях больше matr[i][j], то добавлять эти позиции в список в порядке возрастания значений на этих позициях
                Далее для каждой позиции из выбранных элементов:
                    matr[i][j] = максимум из f(matr, следующая позиция, n, m) и matr[i][j]
                Вернуть matr[i][j]
            }
            */
           return 0;
        }
};

//TODO: Как же мне впадлу разворачивать эту рекурсию 
int find_f(const std::vector<std::vector<int>> &matrix, int prev_num, std::vector<std::vector<int>> &dp, std::vector<std::vector<bool>> &marks, 
    size_t i, size_t j, size_t last_i, size_t last_j) {
    if (marks[i][j] || prev_num >= matrix[i][j]) {
        return 0;
    }
    if (dp[i][j] > 1) {
        return dp[i][j];
    }
    marks[i][j] = true;
    if (j > 0) {
        dp[i][j] = std::max(find_f(matrix, matrix[i][j], dp, marks, i,j-1,last_i,last_j) + 1, dp[i][j]);
    }
    if (i > 0) {
        dp[i][j] = std::max(find_f(matrix, matrix[i][j], dp, marks, i-1,j,last_i,last_j) + 1, dp[i][j]);
    }
    if (j < last_j) {
        dp[i][j] = std::max(find_f(matrix, matrix[i][j], dp, marks, i,j+1,last_i,last_j) + 1, dp[i][j]);
    }
    if (i < last_i) {
        dp[i][j] = std::max(find_f(matrix, matrix[i][j], dp, marks, i+1,j,last_i,last_j) + 1, dp[i][j]);
    }
    marks[i][j] = false;
    return dp[i][j];
}

int find_longest_path_in_matrix(const std::vector<std::vector<int>> &matrix) {
    size_t n = matrix.size(), m = matrix[0].size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m));
    std::vector<std::vector<bool>> marks(n, std::vector<bool>(m));
    int max_path = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            dp[i][j] = 1;
            marks[i][j] = false;
        }
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            max_path = std::max(max_path, find_f(matrix, INT_MIN, dp, marks, i, j, n-1, m-1));
        }
    }
    return max_path;
}

int main(void) {
    /*
    0 1 2
    1 5 3
    8 7 7
    */
    std::vector<std::vector<int>> matrix = {{0,1,2}, {1,5,3}, {8,7,7}};
    std::cout << find_longest_path_in_matrix(matrix) << std::endl;
    return 0;
}