#include <iostream>
#include <vector>
#include <climits>

//SUCCESS

int main(void) {
    int t = 0, n = 0, m = 0, tmp, count;
    std::vector<int> rows, cols;
    bool on_cross;
    int cur_max = INT_MIN;
    rows.reserve(20000);
    cols.reserve(20000);
    std::cin >> t;
    while (t) {
        std::cin >> n >> m;
        std::vector<std::vector<int>> matr(n, std::vector<int>(m));
        cur_max = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> tmp;
                if (tmp > cur_max) {
                    cur_max = tmp;
                }
                matr[i][j] = tmp;
            }
        }
        rows.clear();
        cols.clear();
        rows.resize(n, 0);
        cols.resize(m, 0);
        count = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matr[i][j] == cur_max) {
                    ++rows[i];
                    ++cols[j];
                    ++count;
                }
            }
        }
        on_cross = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((rows[i] + cols[j] - (matr[i][j] == cur_max)) == count) {
                    on_cross = true;
                    goto NEXT_STEP;
                }
            }
        }
        NEXT_STEP:
        if (on_cross) {
            std::cout << cur_max - 1 << std::endl;
        } else {
            std::cout << cur_max << std::endl;
        }
        --t;
    }
    return 0;
}