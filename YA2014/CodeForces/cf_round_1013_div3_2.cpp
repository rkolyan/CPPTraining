#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

//SUCCESS - легкая

using number_t = unsigned int;
using count_t = unsigned int;

int main(void) {
    unsigned int N = 0, M = 0, x = 0, count = 0, m_count = 0, min_elem = 0;
    bool flag = false;
    std::vector<number_t> nums;

    std::cin >> N;
    for (unsigned int i = 0; i < N; i++) {
        std::cin >> M >> x;
        nums.resize(M);
        for (auto &element : nums) {
            std::cin >> element;
        }
        std::sort(nums.begin(), nums.end(), [](int a, int b) {return b < a;});
        count = 0;
        m_count = 0;
        for (const auto &num : nums) {
            m_count++;
            min_elem = num;
            if (min_elem * m_count >= x) {
                count++;
                m_count = 0;
            }
        }
        std::cout << count << std::endl;
    }
    return 0;
}