#include <vector>

//SUCCESS, 8 ms, победил 96.7 %, сделал через сортировку посчетом, есть люди с 0 ms, они вместо freq используют bitset, чтобы уменьшить количество промахов

class Solution {
    private:
    #define MAX_N 100000
    public:
        int partitionArray(std::vector<int>& nums, int k) {
            /*
             */
            int freq[MAX_N + 1] = {0};
            int count = 0;
            for (const auto& num : nums) {
                ++freq[num];
            }
            for (int i = 0; i <= MAX_N; ++i) {
                if (freq[i]) {
                    ++count;
                    i += k;
                }
            }
            return count;
        }
    };

int main(void) {
    return 0;
}