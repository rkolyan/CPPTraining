#include <vector>
#include <array>



//SUCCESS, моё решение имеет скорость 208 ms, побеждает 86 %
/*
Вот 2 решения за 16ms
Решение 1:
#pragma GCC optimize("O3", "unroll-loops")

const auto _ = std::cin.tie(nullptr)->sync_with_stdio(false);

#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
  struct ___ { static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; } };
  std::atexit(&___::_);
  return 0;
}();
#endif
class Solution {
public:
    int n, m;
    vector<vector<int>> grid;
    vector<pair<int,int>> directions = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    
    // Get the clockwise 90-degree turn direction
    int get_clock_wise_turn(int dir) {
        // directions: 0: down-right, 1: down-left, 2: up-right, 3: up-left
        // Clockwise turns:
        // down-right (0) -> down-left (1)
        // down-left (1) -> up-left (3)
        // up-right (2) -> down-right (0)
        // up-left (3) -> up-right (2)
        if (dir == 0) return 1;
        if (dir == 1) return 3;
        if (dir == 2) return 0;
        if (dir == 3) return 2;
        return -1;
    }
    
    int solveRE(int i, int j, int dir, int turned, int step) {
        if (i < 0 || j < 0 || i >= n || j >= m) return 0;
        
        int expected = (step == 0) ? 1 : ((step % 2 == 1) ? 2 : 0);
        if (grid[i][j] != expected) return 0;
        
        // Continue in the same direction
        int best = 1 + solveRE(i + directions[dir].first, j + directions[dir].second, dir, turned, step + 1);
        
        // Try turning clockwise (only if we haven't turned yet)
        if (!turned) {
            int new_dir = get_clock_wise_turn(dir);
            best = max(best, 1 + solveRE(i + directions[new_dir].first, j + directions[new_dir].second, new_dir, 1, step + 1));
        }
        
        return best;
    }
    
    int lenOfVDiagonal(vector<vector<int>>& g) {
        grid = g;
        n = grid.size();
        m = grid[0].size();
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (int dir = 0; dir < 4; dir++) {
                        ans = max(ans, solveRE(i, j, dir, 0, 0));
                    }
                }
            }
        }
        
        return ans;
    }
};

/////////////////////////////////////////////////
Решение 2:

char grd[502*501+1];
int vsz[501*500][5];
int dlt[4];

pair<int,int> init(const vector<vector<int>>& grid) {
    int M = size(grid[0]) + 1;
    char *p = grd + M; memset(grd, 4, M);
    for (const auto &r : grid) {
        *p++ = 4;
        for (int x : r) *p++ = x;
    }
    memset(p, 4, M+1);
    dlt[0] = -M - 1;  dlt[1] = -M + 1;  dlt[2] = M + 1;  dlt[3] = M - 1;
    return {M+1, p-grd};
}

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        auto [bg, ed] = init(grid);
        for (int i = bg, j = 0, d0 = dlt[0], d1 = dlt[1]; i != ed; ++i, ++j) {
            char u = grd[i], d = !(u & 5);
            vsz[j][4] = (u ^ grd[i + d0]) == 2 ? 1 + vsz[j+d0][4] : d;
            vsz[j][1] = (u ^ grd[i + d1]) == 2 ? 1 + vsz[j+d1][1] : d;
        }
        for (int i = ed-1, j = ed-bg-1, d2 = dlt[2], d3 = dlt[3]; j >= 0; --i, --j) {
            char u = grd[i], d = !(u & 5);
            vsz[j][2] = (u ^ grd[i + d2]) == 2 ? 1 + vsz[j+d2][2] : d;
            vsz[j][3] = (u ^ grd[i + d3]) == 2 ? 1 + vsz[j+d3][3] : d;
        }

        for (int i = bg, j = 0, d0 = dlt[0], d1 = dlt[1]; i != ed; ++i, ++j) {
            char u = grd[i];
            int b0 = vsz[j][1], b1 = vsz[j][2];
            vsz[j][0] = (u ^ grd[i + d0]) == 2 ? max(1 + vsz[j+d0][0], b0) : b0;
            vsz[j][1] = (u ^ grd[i + d1]) == 2 ? max(1 + vsz[j+d1][1], b1) : b1;
        }
        for (int i = ed-1, j = ed-bg-1, d2 = dlt[2], d3 = dlt[3]; j >= 0; --i, --j) {
            char u = grd[i];
            int b2 = vsz[j][3], b3 = vsz[j][4];
            vsz[j][2] = (u ^ grd[i + d2]) == 2 ? max(1 + vsz[j+d2][2], b2) : b2;
            vsz[j][3] = (u ^ grd[i + d3]) == 2 ? max(1 + vsz[j+d3][3], b3) : b3;
        }
        int res = 0, f = 0;
        for (int i = bg, j = 0; i != ed; ++i, ++j) if (grd[i] == 1) {
            f = 1;
            for (int d = 0; d < 4; ++d) if (grd[i+dlt[d]] == 2) res = max(res, vsz[j+dlt[d]][d]);
        }
        return f ? res+1 : 0;
    }
};

*/
/*
You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.

A V-shaped diagonal segment is defined as:

    The segment starts with 1.
    The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
    The segment:
        Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
        Continues the sequence in the same diagonal direction.
        Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.

*/



//Моё решение
class Solution {
private:
    enum DIRECTION {
        UP_LEFT = 0,
        UP_RIGHT,
        DOWN_RIGHT,
        DOWN_LEFT,
        DIRECTION_MODULO
    };
    int directions[DIRECTION_MODULO][2] = {{-1,-1}, {-1,1}, {1,1}, {1,-1}};
    std::vector<std::vector<std::array<std::array<int, DIRECTION_MODULO>, 2>>> dp;
    std::vector<std::vector<std::array<std::array<bool, DIRECTION_MODULO>, 2>>> observed;
    int n, m;
    //Я оказался слишком умный для этой задачи и не понял прикола, что поворот за всё время должен быть только 1
    //std::vector<std::vector<std::array<int, DIRECTION_MODULO>>> dp;
    //std::vector<std::vector<std::array<bool, DIRECTION_MODULO>>> observed;
    /*
    int dfs(const std::vector<std::vector<int>> &grid, int i, int j, DIRECTION cur_dir, int prev_num) {
        if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 2 - prev_num) {
            return 0;
        }
        int straight, rotated;

        if (!observed[i][j][cur_dir]) {
            auto &direction = directions[cur_dir];
            //Для предотвращения переходов в циклы сначала пишем, что эта часть обследована (по умолчанию длина пути = 0)
            observed[i][j][cur_dir] = true;
            dp[i][j][cur_dir] = dfs(grid, i + direction[0], j + direction[1], cur_dir, grid[i][j]);
        }
        straight = dp[i][j][cur_dir];

        cur_dir = static_cast<DIRECTION>((cur_dir + 1) % DIRECTION_MODULO);
        
        if (!observed[i][j][cur_dir]) {
            auto &direction = directions[cur_dir];
            observed[i][j][cur_dir] = true;
            dp[i][j][cur_dir] = dfs(grid, i + direction[0], j + direction[1], cur_dir, grid[i][j]);
        }
        rotated = dp[i][j][cur_dir];

        return std::max(straight, rotated) + 1;
    }
    */
   
    int dfs(const std::vector<std::vector<int>> &grid, int i, int j, DIRECTION cur_dir, int prev_num = 0, int rotate_flag = 1) {
        if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 2 - prev_num) {
            return 0;
        }
        int path_len = 0;

        if (!observed[i][j][rotate_flag][cur_dir]) {
            auto &direction = directions[cur_dir];
            //Для предотвращения переходов в циклы сначала пишем, что эта часть обследована (по умолчанию длина пути = 0)
            observed[i][j][rotate_flag][cur_dir] = true;
            dp[i][j][rotate_flag][cur_dir] = dfs(grid, i + direction[0], j + direction[1], cur_dir, grid[i][j], rotate_flag);
        }
        path_len = dp[i][j][rotate_flag][cur_dir];

        if (rotate_flag) {
            cur_dir = static_cast<DIRECTION>((cur_dir + 1) % DIRECTION_MODULO);
            
            if (!observed[i][j][0][cur_dir]) {
                auto &direction = directions[cur_dir];
                observed[i][j][0][cur_dir] = true;
                dp[i][j][0][cur_dir] = dfs(grid, i + direction[0], j + direction[1], cur_dir, grid[i][j], 0);
            }
            path_len = std::max(dp[i][j][0][cur_dir], path_len);
        }

        return path_len + 1;
    }


public:
    int lenOfVDiagonal(std::vector<std::vector<int>>& grid) {
        n = static_cast<int>(grid.size());
        m = static_cast<int>(grid[0].size());
        dp.resize(n, std::vector<std::array<std::array<int, DIRECTION_MODULO>, 2>>(m));
        observed.resize(n, std::vector<std::array<std::array<bool, DIRECTION_MODULO>, 2>>(m));
        int max_path = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    for (int dir = UP_LEFT; dir < DIRECTION_MODULO; ++dir) {
                        auto &direction = directions[dir];
                        max_path = std::max(dfs(grid, i + direction[0], j + direction[1], static_cast<DIRECTION>(dir)) + 1, max_path);
                    }
                }
            }
        }
        return max_path;
    }
};

#include <iostream>

int main(void) {
    std::vector<std::vector<int>> grid = {{2,2,2,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}};
    std::vector<std::vector<int>> grid2 = {{2,2,1,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}};
    std::vector<std::vector<int>> grid1 = {{1,1,0,1,1,1,0,2,1,2},{0,1,0,0,2,1,2,1,2,0},{2,0,2,0,2,1,0,2,0,1},{2,2,2,0,2,0,2,0,1,0},{1,0,1,0,1,0,1,0,1,1}};
    /*
    1 1 0 1 1 1 0 2 1 2
    0 1 0 0 2 1 2 1 2 0
    2 0 2 0 2 1 0 2 0 1
    2 2 2 0 2 0 2 0 1 0
    1 0 1 0 1 0 1 0 1 1
    */
    Solution sol;

    std::cout << sol.lenOfVDiagonal(grid1) << std::endl;

    return 0;
}