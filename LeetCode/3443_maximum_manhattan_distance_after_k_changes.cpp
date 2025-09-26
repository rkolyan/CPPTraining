#include <string>

//SUCCESS, 63 ms, побеждает 80%
/*
Самое быстрое решение за 0 ms
Такое банальное, что даже грустно, что до него не догадался


auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
auto init2 = atexit([]() { ofstream("display_runtime.txt") << 0; });
class Solution {
public:
    int maxDistance(string s, int k) {
        int ans = 0;
        char dir[4][2] = {{'N', 'E'}, {'N', 'W'}, {'S', 'E'}, {'S', 'W'}};
        for (auto d : dir) {
            for (int i = 0, curr = 0, t = k; i < s.size(); ++i) {
                if (s[i] == d[0] || s[i] == d[1]) {
                    if (t > 0) {
                        t--;
                        curr++;
                    } else
                        curr--;
                } else
                    curr++;
                ans = max(ans, curr);
            }
        }
        return ans;
    }
*/

class Solution {
    private:
        enum direction_t {
            N,
            S,
            E,
            W,
            DIRECTION_COUNT
        };
    public:
        int maxDistance(std::string s, int k) {
            int counts[DIRECTION_COUNT] = {0};
            int max_len = 0, cur_len = 0, x = 0, y = 0, tmp_x, tmp_y, delta, tmp_k;
            for (const auto &sym : s) {
                switch (sym)
                {
                case 'N':
                    ++counts[N];
                    ++y;
                    break;
                case 'S':
                    ++counts[S];
                    --y;
                    break;
                case 'E':
                    ++counts[E];
                    ++x;
                    break;
                case 'W':
                    ++counts[W];
                    --x;
                    break;
                }
                cur_len = std::abs(x) + std::abs(y);
                delta = 0;
                tmp_k = k;
                if (x >= 0) {
                    delta = std::min(tmp_k, counts[W]);
                } else {
                    delta = std::min(tmp_k, counts[E]);
                }
                tmp_k = std::max(tmp_k - delta, 0);
                if (y >= 0) {
                    delta += std::min(tmp_k, counts[S]);
                } else {
                    delta += std::min(tmp_k, counts[N]);
                }
                cur_len += 2 * delta;
                max_len = std::max(cur_len, max_len);
            }
            return max_len;
        }
    };

#include <iostream>

int main(void) {
    Solution sol;
    std::cout << sol.maxDistance("EWWE", 1) << std::endl;
}