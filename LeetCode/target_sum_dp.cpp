#include <vector>
#include <map>
using namespace std;

typedef int number_t;
typedef unsigned int count_t;

class Solution {
    public:
        int findTargetSumWays(vector<int>& nums, int target) {
            /*
            1)Используем 2 множества - новое и старое,
            */
            std::map<number_t, count_t> result, tmp;
            tmp[nums.front()]++;
            tmp[-nums.front()]++;
            for (const auto &element : nums) {
                for (const auto &pair : result) {
                    tmp[pair.first + element] += pair.second;
                    tmp[pair.first - element] += pair.second;
                }
                std::swap(result, tmp);
                tmp.clear();
            }
            return result[target];
        }
    };