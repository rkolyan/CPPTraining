#include <vector>
#include <tuple>
#include <stack>


//TODO: Напиши своё решение не опираясь на это
/*
Вот решение списанное, посмотри как оно работает
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat[0].size();
        vector<int> heights(n, 0);
        int res = 0;
        for (const auto& row : mat) {
            for (int i = 0; i < n; ++i) {
                heights[i] = (row[i] == 0) ? 0 : heights[i] + 1;
            }
            stack<vector<int>> st;
            st.push({-1, 0, -1});
            for (int i = 0; i < n; ++i) {
                int h = heights[i];
                while (st.top()[2] >= h) {
                    st.pop();
                }
                auto& top = st.top();
                int j = top[0];
                int prev = top[1];
                int cur = prev + (i - j) * h;
                st.push({i, cur, h});
                res += cur;
            }
        }
        return res;
    }
};
*/

class Solution {
public:
    int numSubmat(std::vector<std::vector<int>>& mat) {
        std::vector<int> height(mat[0].size(), 0);
        std::stack<std::tuple<int, int, int>> stack;
        for (const auto &col : mat) {
            height[0] = col[0];
            for (std::size_t i = 1; i < col.size(); ++i) {
                if (col[i]) {
                    height[i] = height[i-1] + 1;
                } else {
                    height[i] = 0;
                }
            }

        }
        return 0;
    }
};

#include <iostream>

int main(void) {
    std::vector<std::vector<int>> mat1 = {{1,0,1},{1,1,0},{1,1,0}}, mat2 = {{0,1,1,0},{0,1,1,1},{1,1,1,0}};
    Solution sol;
    std::cout << sol.numSubmat(mat1) << std::endl;
    std::cout << sol.numSubmat(mat2) << std::endl;
    return 0;
}