#include <vector>
#include <unordered_map>
/*
SUCCESS, но у меня не производительное решение из-за большого количества операций вставки и поиска (100 ms)

Вот оптимальное решение через хеш-таблицы
Чел просто сначала вставил все числа в таблицу, потом искал начало последовательности и с него делал проверку

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int maxlen = 0;
        for(int num:s)
        {
            if(s.find(num-1)==s.end())
            {
                int cur=num;
                int count=1;
                while(s.find(cur+1)!=s.end())
                {
                    cur++;
                    count++;
                }
                maxlen=max(maxlen,count);
            }
        }
        return maxlen;
    }
};

Можно ещё решить через непересекающиеся множества со сжатием путей и прочей лабуды, но мне лень её реализовывать

*/
class Solution {
    public:
        int longestConsecutive(std::vector<int>& nums) {
            /*
            Итак, нужно найти максимальную длину последовательности, в которых числа идут последовательно, типа 1,2,3,4...
            Итак, очередь приоритетов использовать нельзя, тогда сложность будет O(nlogn), а нужно O(n)
            2 хеш-таблицы, в первой храним левую границу, во второй левую

            */
            std::unordered_map<int, int> lefts, rights;
            int max_len = 0, cur_len = 0;
            lefts.reserve(nums.size());
            rights.reserve(nums.size());
            auto left_iter = lefts.begin();
            auto right_iter = rights.begin();
            for (const auto &num : nums) {
                left_iter = lefts.find(num - 1);
                right_iter = rights.find(num + 1);
                if (left_iter != lefts.end()) {
                    auto left_bound = (*left_iter).second;
                    cur_len = num - left_bound;
                    if (right_iter != rights.end()) {
                        auto right_bound = (*right_iter).second;
                        cur_len += right_bound - num;
                        if (lefts.find(right_bound) == lefts.end() || lefts[right_bound] > left_bound) {
                            lefts[right_bound] = left_bound;
                        }
                        if (rights.find(left_bound) == rights.end() || rights[left_bound] < right_bound) {
                            rights[left_bound] = right_bound;
                        }
                        //rights.erase(right_iter);
                    } else {
                        if (lefts.find(num) == lefts.end() || lefts[num] > left_bound) {
                            lefts[num] = left_bound;
                        }
                        if (rights.find(left_bound) == lefts.end() || rights[left_bound] < num) {
                            rights[left_bound] = num;
                        }
                    }
                    //lefts.erase(left_iter);
                    max_len = std::max(max_len, cur_len + 1);
                } else if (right_iter != rights.end()) {
                    auto right_bound = (*right_iter).second;
                    cur_len = right_bound - num;
                    if (rights.find(num) == rights.end() || rights[num] < right_bound) {
                        rights[num] = right_bound;
                    }
                    if (lefts.find(right_bound) == lefts.end() || lefts[right_bound] > num) {
                        lefts[right_bound] = num;
                    }
                    //rights.erase(right_iter);
                    max_len = std::max(max_len, cur_len + 1);
                } else {
                    if (rights.find(num) == rights.end()) {
                        rights[num] = num;
                    }
                    if (lefts.find(num) == lefts.end()) {
                        lefts[num] = num;
                    }
                    max_len = std::max(max_len, 1);
                }
            }
            return max_len;
        }
    };

#include <iostream>

int main(void) {
    std::vector<int> nums1 {100,4,200,1,3,2}, nums2 {0,3,7,2,5,8,4,6,0,1}, nums3 {1,0,1,2};
    Solution sol;
    std::cout << sol.longestConsecutive(nums1) << std::endl;
    std::cout << sol.longestConsecutive(nums2) << std::endl;
    std::cout << sol.longestConsecutive(nums3) << std::endl;
    return 0;
}