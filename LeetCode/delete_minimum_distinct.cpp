#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <functional>

class Solution {
    public:
        int minDeletion(std::string s, int k) {
            int count = 0;
            std::map<std::string::value_type, std::size_t> symmap;
            for (const auto &sym : s) {
                symmap[sym]++;
            }
            using mypair = std::pair<std::size_t, std::string::value_type>;
            std::vector<mypair> container;
            container.reserve(symmap.size());
            std::priority_queue<mypair, std::vector<mypair>, std::greater<mypair>> queue(std::greater<mypair>{}, std::move(container));
            for (const auto &pair : symmap) {
                queue.emplace(pair.second, pair.first);
            }
            std::cout << std::endl;
            while (queue.size() > k) {
                std::cout << queue.top().first << ' ';
                count += queue.top().first;
                queue.pop(); 
            }
            return count;
        }
    };

int main(void) {
    std::string str;
    int k = 0;
    std::getline(std::cin, str);
    std::cin >> k;
    std::cout << Solution().minDeletion(str, k) << std::endl;
    return 0;
}