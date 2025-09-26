#include <vector>

//SUCCESS, Решение почему-то занимает 254 ms (хотя побеждает 69 %)... Че-то многовато для O(n x m) обхода матрицы...
/*
Вот за 0 ms, очень конечно лаконично, но не каждый догадается, что INT_MIN - INT_MAX + 1 == 0
Интересно, если б не atexit какое бы реальное время оно бы показало...

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        atexit(+[](){ofstream("display_runtime.txt") << 0 << '\n';});
        int minrow=INT_MAX,maxrow=INT_MIN,mincol=INT_MAX,maxcol=INT_MIN;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    minrow=min(i,minrow);
                    maxrow=max(i,maxrow);
                    mincol=min(j,mincol);
                    maxcol=max(j,maxcol);
                }
            }
        }
        return (maxrow-minrow+1)*(maxcol-mincol+1);
        
    }
};
*/


class Solution {
public:
    int minimumArea(std::vector<std::vector<int>>& grid) {
        /*
        Итак, 1)ищем первую i,j, где есть 1-ца и ставим 
        */
        int left = -1, right, up, down;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j){
                if (grid[i][j]) {
                    left = j;
                    right = j;
                    up = i;
                    down = i;
                    goto NEXT;
                }
            }
        }
        NEXT:
        for (int i = up; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j]) {
                    if (i > down) {
                        down = i;
                    }
                    if (j < left) {
                        left = j;
                    }
                    if (j > right) {
                        right = j;
                    }
                }
            }
        }
        if (left != -1) {
            return (down - up + 1) * (right - left + 1);
        }
        return 0;
    }
};

#include <iostream>

int main(void) {
    std::vector<std::vector<int>> mat1{{0,1,0},{1,0,1}}, mat2{{1,0},{0,0}};
    Solution sol;
    std::cout << sol.minimumArea(mat1) << std::endl;
    //std::cout << sol.minimumArea(mat2) << std::endl;
    return 0;
}