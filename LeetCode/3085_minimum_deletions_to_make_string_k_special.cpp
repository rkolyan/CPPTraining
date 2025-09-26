#include <string>
#include <vector>
#include <algorithm>
#include <climits>

//SUCCESS, 0 ms, побеждает 100 %, уф, этот прицел просто имба (хотя и смог пройти только через 4 попытки)

class Solution {
    public:
        int minimumDeletions(std::string word, int k) {
            constexpr int CHARS_COUNT = 'z' - 'a' + 1;
            int chars_count[CHARS_COUNT] = {0};
            std::vector<int> freq;
            freq.reserve(CHARS_COUNT);
    
            int sum1 = 0, sum2 = word.size(), min_count = INT_MAX;
            for (const auto& sym : word) {
                ++chars_count[sym - 'a'];
            }
            for (int i = 0; i < CHARS_COUNT; ++i) {
                if (chars_count[i]) {
                    freq.push_back(chars_count[i]);
                }
            }
            if (freq.size() == 1) {
                return 0;
            }
            std::sort(freq.begin(), freq.end());
            int i_begin = 0, i_end = 0, i_end_bound = 0;
            while (i_end < freq.size()) {
                while (i_end < freq.size() && freq[i_end] - freq[i_begin] <= k) {
                    sum2 -= freq[i_end];
                    //i_end_bound = i_end;
                    ++i_end;
                }
                min_count = std::min(
                    min_count,
                    sum1 + std::max(
                               0, (sum2 - (static_cast<int>(freq.size()) - i_end) *
                                              (freq[i_begin] + k))));
                if (i_begin < i_end) {
                    sum1 += freq[i_begin];
                    ++i_begin;
                }
                /*
                if (i_begin < freq.size()) {
                    min_count = std::min(min_count, sum1 + std::max(0,(sum2 -
                (static_cast<int>(freq.size()) - i_end) * (freq[i_begin] + k))));
                }
                */
            }
            return min_count;
        }
    };

#include <iostream>
int main(void) {
    Solution sol;
    std::cout << sol.minimumDeletions("aabcaba", 0) << std::endl;
    std::cout << sol.minimumDeletions("dabdcbdcdcd", 2) << std::endl;
    std::cout << sol.minimumDeletions("aaabaaa", 2) << std::endl;
    std::cout << sol.minimumDeletions("ahahnhahhah", 1) << std::endl;
    std::cout << sol.minimumDeletions("eeffmeefexefefffefemeexfeeffeefmfhxemmeeffffmfmmfffeeeffeffeffqffffefmeeeeefffmeffffffefefqfefffmfffmefeeeefexeffffffemffeffffffffemfeefeffffefjefxfffffffemfffffmfffefeemfeffffffmfffffeefefeffxfefefffeefffeqeffeefeemfefeemfffxfxeffffffeffffmfffexfffffee", 54) << std::endl;
    return 0;
}