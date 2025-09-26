#include <iostream>
#include <set>
#include <vector>
#include <map>

//SUCCESS - легкая

using number_t = unsigned int;
using count_t = unsigned int;

int main(void) {
    unsigned int N = 0, M = 0, index = 0, tmp = 0;
    bool flag = false;
    std::multiset<number_t> nums = {0, 1, 0, 3, 2, 0, 2, 5};
    std::cin >> N;
    for (unsigned int i = 0; i < N; i++) {
        flag = true;
        std::cin >> M;
        nums = {0,1,0,3,2,0,2,5};
        index = 0;
        for (unsigned int j = 0; j < M; j++) {
            std::cin >> tmp;
            if (flag) {
                nums.extract(tmp);
                if (!nums.size()) {
                    index = j + 1;
                    flag = false;
                }
            }
        }
        std::cout << index << std::endl;
    }
    return 0;
}