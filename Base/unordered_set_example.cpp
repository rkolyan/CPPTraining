#include <unordered_map>
#include <vector>

int main(void) {
    std::vector<int> nums = {1, 1, 2, 3, 4, 5};
    std::unordered_map<int, int> map;
    map.reserve(nums.size());
    return 0;
}