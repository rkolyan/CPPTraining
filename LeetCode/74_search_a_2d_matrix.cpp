#include <vector>

//SUCCESS, хотя я не помню, это финальный результат или нет...

class Solution {
    public:
        bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
            //1)Ищем по первым элементам в строке, 2)Ищем в строке
            if (!matrix.size()) {
                return false;
            }
            int left = 0, right = matrix.size(), mid, up;
            while (right - left > 1) {
                mid = (right + left)/2;
                if (matrix[mid][0] > target) {
                    right = mid - 1;
                } else {
                    left = mid;
                }
            }
            if (matrix[left][0] > target) {
                return false;
            }
            up = std::min(right, static_cast<int>(matrix.size()-1));
            if (matrix[up][0] <= target) {
                left = up;
            }
            const auto row = matrix[left];
            left = 0;
            right = row.size()-1;
            while (right >= left) {
                mid = (left + right)/2;
                if (row[mid] > target) {
                    right = mid - 1;
                } else if (row[mid] < target) {
                    left = mid+1;
                } else {
                    return true;
                }
            }
            if (left < row.size() && row[left] == target) {
                return true;
            }
            return false;
        }
    };

#include <iostream>

int main(void) {
    std::vector<std::vector<int>> matrix1 = {{1,3,5,7}, {10,11,16,20},{23,30,34,60}}, matrix2 = {{1}};
    Solution sol;
    std::cout << sol.searchMatrix(matrix1, 24) << std::endl;
    std::cout << sol.searchMatrix(matrix2, 1) << std::endl;
    std::cout << sol.searchMatrix(matrix2, 2) << std::endl;
    return 0;
}