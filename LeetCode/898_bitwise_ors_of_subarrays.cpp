#include <vector>
#include <unordered_set>

//Наивная версия, ненаивную ты сам придумай
class Solution {
public:
    int subarrayBitwiseORs(std::vector<int>& arr) {      
        std::unordered_set<int> prev, curr, result;
        prev.reserve(arr.size() * arr.size());
        curr.reserve(prev.size());
        result.reserve(prev.size());
        for (const auto &element : arr) {
            for (const auto &prev_element : prev) {
                auto tmp = element | prev_element;
                curr.emplace(tmp);
                result.emplace(tmp);
            }
            curr.emplace(element);
            result.emplace(element);
            std::swap(prev, curr);
            curr.clear();
        }
        return static_cast<int>(result.size());
    }
};

#include <iostream>

int main(void) {
    std::vector<int> arr = {108,121,9,85,27};
    Solution sol;
    std::cout << sol.subarrayBitwiseORs(arr) << std::endl;
    return 0;
}