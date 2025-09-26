#include <iostream>
#include <vector>
#include <queue>
#include <climits>

//SUCCESS
typedef int len_t;
#define LEN_MAX INT_MAX
typedef unsigned int row_t;
typedef unsigned int column_t;
using coords_t = std::pair<row_t, column_t>;
using path_t = std::pair<len_t, int>;
using len_coords_t = std::pair<path_t, coords_t>;
inline len_t get_len(len_coords_t len_coords) {
    return len_coords.first.first;
}
inline len_t get_dt(len_coords_t len_coords) {
    return len_coords.first.second;
}
inline row_t get_row(len_coords_t len_coords) {
    return len_coords.second.first;
}
inline column_t get_column(len_coords_t len_coords) {
    return len_coords.second.second;
}
class Solution {
public:
    int minTimeToReach(std::vector<std::vector<int>>& moveTime) {
        const unsigned int &N = moveTime.size(), &M = moveTime[0].size();
        unsigned int dist = 0;
        len_coords_t tmp;
        len_t currDist = 0;
        len_t dt = 1;
        row_t row = 0;
        column_t column = 0;
        std::priority_queue<len_coords_t, std::vector<len_coords_t>, std::greater<len_coords_t>> queue;
        len_t d[N][M];
        for (row_t i = 0; i < N; ++i) {
            for (column_t j = 0; j < M; ++j) {
                d[i][j] = LEN_MAX;
            }
        }
        queue.emplace(path_t{0, 1}, coords_t{0, 0});
        while (!queue.empty()) {
            tmp = queue.top();
            queue.pop();
            currDist = get_len(tmp);
            dt = get_dt(tmp);
            column = get_column(tmp);
            row = get_row(tmp);

            if (currDist > d[row][column]) {
                continue;
            }
            currDist += dt;
            if (row > 0) {
                dist = std::max(moveTime[row - 1][column]+1, currDist);
                auto &d_cur = d[row - 1][column];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(path_t{dist, 3 - dt}, coords_t{row - 1, column});
                }
            }
            if (row < N - 1) {
                dist = std::max(moveTime[row + 1][column]+1, currDist);
                auto &d_cur = d[row + 1][column];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(path_t{dist, 3 - dt}, coords_t{row + 1, column});
                }
            }
            if (column > 0) {
                dist = std::max(moveTime[row][column - 1]+1, currDist);
                auto &d_cur = d[row][column - 1];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(path_t{dist, 3 - dt}, coords_t{row, column - 1});
                }
            }
            if (column < M - 1) {
                dist = std::max(moveTime[row][column + 1]+1, currDist);
                auto &d_cur = d[row][column + 1];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(path_t{dist, 3 - dt}, coords_t{row, column + 1});
                }
            }
        }
        return d[N-1][M-1];
    }
    /*
    int minTimeToReach1(std::vector<std::vector<int>>& moveTime) {
        const unsigned int &N = moveTime.size(), &M = moveTime[0].size();
        unsigned int dist = 0;
        len_coords_t tmp;
        len_t currDist = 0;
        row_t row = 0;
        column_t column = 0;
        std::priority_queue<len_coords_t, std::vector<len_coords_t>, std::greater<len_coords_t>> queue;
        len_t d[N][M];
        for (row_t i = 0; i < N; ++i) {
            for (column_t j = 0; j < M; ++j) {
                d[i][j] = LEN_MAX;
            }
        }
        queue.emplace(len_t{0}, coords_t{0, 0});
        while (!queue.empty()) {
            tmp = queue.top();
            queue.pop();
            currDist = get_len(tmp);
            column = get_column(tmp);
            row = get_row(tmp);

            if (currDist > d[row][column]) {
                continue;
            }
            ++currDist;
            if (row > 0) {
                dist = std::max(moveTime[row - 1][column]+1, currDist);
                auto &d_cur = d[row - 1][column];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(dist, coords_t{row - 1, column});
                }
            }
            if (row < N - 1) {
                dist = std::max(moveTime[row + 1][column]+1, currDist);
                auto &d_cur = d[row + 1][column];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(dist, coords_t{row + 1, column});
                }
            }
            if (column > 0) {
                dist = std::max(moveTime[row][column - 1]+1, currDist);
                auto &d_cur = d[row][column - 1];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(dist, coords_t{row, column - 1});
                }
            }
            if (column < M - 1) {
                dist = std::max(moveTime[row][column + 1]+1, currDist);
                auto &d_cur = d[row][column + 1];
                if (dist < d_cur) {
                    d_cur = dist;
                    queue.emplace(dist, coords_t{row, column + 1});
                }
            }
        }
        return d[N-1][M-1];
    }
    std::vector<std::vector<int>> specialGrid(int n) {
        std::vector<std::vector<int>> result(1 << n, std::vector<int>(1 << n));
        int maximum = 1 << n, add = 1;
        for (int b = 1; b < maximum; b <<= 1) {
            for (int i = 0; i < b; ++i) {
                for (int j = maximum - b; j < maximum; ++j) {
                    result[i + b][j] = result[i][j] + add;
                    result[i + b][j - b] = result[i][j] + 2 * add;
                    result[i][j - b] = result[i][j] + 3 * add;
                }
            }
            add <<= 2;
        }
        return result;
    }
    */
};
int main(void) {
    /*
    std::vector<std::vector<int>> matr1 {{0, 0, 0}, {9, 9, 0}, {0, 0, 0}, {0, 100, 100}, {0, 0, 0}};
    std::vector<std::vector<int>> matr2 {{0,0,0,0,0}, {100,100,100,100,0}, {0,0,0,100,0}, {0,100,0,0,0}, {0,100,100,100,100}, {0,0,0,0,0}},
    matr3 {{0, 4},{4, 4}}, matr4 {{0,0,0},{0,0,0}}, matr5 {{0, 1}, {1, 2}};
    std::cout << Solution().minTimeToReach(matr1) << std::endl;
    std::cout << Solution().minTimeToReach(matr2) << std::endl;
    std::cout << Solution().minTimeToReach(matr3) << std::endl;
    std::cout << Solution().minTimeToReach(matr4) << std::endl;
    std::cout << Solution().minTimeToReach(matr5) << std::endl;
    */
    std::vector<std::vector<int>> matr1{{0, 4}, {4,4}}, matr2{{0,0,0,0},{0,0,0,0}}, matr3{{0,1},{1,2}};
    std::cout << Solution().minTimeToReach(matr1) << std::endl;
    std::cout << Solution().minTimeToReach(matr2) << std::endl;
    std::cout << Solution().minTimeToReach(matr3) << std::endl;
    /*
    auto result = Solution().specialGrid(3);
    for (const auto &row : result) {
        for (const auto &element: row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
    */
    return 0;
}