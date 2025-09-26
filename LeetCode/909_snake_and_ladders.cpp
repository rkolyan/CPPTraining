#include <iostream>
#include <vector>
#include <queue>

//SUCCESS, но, блин, а почему я отказался делать это через поиск в ширину, а сделал через Дейкстру...

class Solution {
    private:
        typedef int len_t;
        typedef int player_pos_t;
        using step_t = std::pair<len_t, player_pos_t>;
        inline player_pos_t FIX_POSITION(int pos) {
            return pos - 1;
        }
        inline void fill_indexes(int i_array[6], int j_array[6], int &count, player_pos_t pos, const int n, player_pos_t end) {
            count = std::min(6, end - pos);
            ++pos;
            int row = pos / n, column = pos % n;
            int tmp_count = count, tmp_end = 0, s = 0;
            if (row & 1) {
                tmp_end = -1;
                s = -1;
                column = n - 1 - column;
            } else {
                tmp_end = n;
                s = 1;
            }
            row = n - 1 - row;
            int j = 0;
            while (tmp_count) {
                for (j = column; j != tmp_end && tmp_count; j += s, --tmp_count) {
                    i_array[count - tmp_count] = row;
                    j_array[count - tmp_count] = j;
                }
                s = -s;
                column = tmp_end + s;
                tmp_end = n - 1 - tmp_end;
                --row;
            }
        }
    public:
        int snakesAndLadders(std::vector<std::vector<int>>& board) {
            /*
            Итак, у нас дана доска размера nxn, начинаем с позиции board[n-1][0] и двигаемся попеременно меняя направление то налево то направо
            Ой, кароч, обычная задача на динамическое программирование, просто делаем dp[n*n], берём алгоритм Дейкстры и работаем от него
            }
            */
            const auto &N = board.size();
            std::priority_queue<step_t, std::vector<step_t>, std::greater<step_t>> queue = [&]{
                std::vector<step_t> buffer;
                buffer.reserve(N);
                return std::priority_queue<step_t, std::vector<step_t>, std::greater<step_t>>(std::greater<step_t>{}, std::move(buffer));
            }();
            std::vector<len_t> d(N * N, -1);
            len_t len = 0;
            player_pos_t pos = 0, pos_end = N * N - 1;
            int i_array[6] = {0}, j_array[6] = {0};
            int array_count = 6, i = 0, j = 0, last = 0;
            queue.emplace(0, 0);
            while (!queue.empty()) {
                const auto &step = queue.top();
                len = step.first;
                pos = step.second;
                queue.pop();
                if (d[pos] == -1 || d[pos] > len) {
                    d[pos] = len;
                    ++len;
                    fill_indexes(i_array, j_array, array_count, pos, N, pos_end);
                    last = -1;
                    for (int k = 0; k < array_count; ++k) {
                        i = i_array[k];
                        j = j_array[k];
                        if (board[i][j] != -1) {
                            queue.emplace(len, FIX_POSITION(board[i][j]));
                        } else {
                            last = k;
                        }
                    }
                    if (last != -1) {
                        queue.emplace(len, pos + last + 1);
                    }
                }
            }
            return d[pos_end];
        }
    };

int main(void) {
    std::vector<std::vector<int>> board1 = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    std::vector<std::vector<int>> board2 = {{-1,-1},{-1,3}};
    std::vector<std::vector<int>> board3 = {{-1,7,-1},{-1,6,9},{-1,-1,2}};
    Solution sol;

    std::cout << sol.snakesAndLadders(board1) << std::endl;
    std::cout << sol.snakesAndLadders(board2) << std::endl;
    std::cout << sol.snakesAndLadders(board3) << std::endl;
    return 0;
}