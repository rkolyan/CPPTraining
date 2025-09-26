#include <iostream>
#include <vector>

//SUCCESS - легкая

using number_t = unsigned int;

int main(void) {
    std::size_t N = 0, M = 0;
    std::vector<number_t> nums;
    std::cin >> N;
    for (unsigned int i = 0; i < N; i++) {
        std::cin >> M;
        if (M & 1) {
            nums.resize(M);
            for (number_t num = 1; num <= M; num++) {
                nums[(num - 1 + num - 1) % M] = num;
            }
            for (const auto &element : nums) {
                std::cout << element << ' '; 
            }
            std::cout << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    /*
    1 2 3 4 5
    1 4 2 5 3
    4 2 5 3 1
    2 5 3 1 4
    5 3 1 4 2
    3 1 4 2 5
    4 1 3 5 2
    1 3 5 2 4
    3 5 2 4 1
    5 2 4 1 3
    2 4 1 3 5

    1 2 3 4
    1 3 2 
    3 2   3
    2   3
      3   4
    1 2 3 4 5 6 7
    1   2 6 3 7 4
      2 6 3 7 4 1
    2 6 3 7 4 1 5
    6 3 7 4 1 5 
    3 7 4 1 5
    7 4 1 5   6
    4 1 5   6   7

    1 3 4 2
    1 2 3 4
    1 3 4 2
    
    4 2 1 3
    1 2 3 4

    2 1 3 4
    1 2 3 4
    1 2 3
    3 2 1
    2 1 3
    1 3 2

    1 2 3 4 5
    2 1 3 5 4

    1 2 3 4 5 6 7
    7 6 5 4 3 2 1
    6 5 4 3 2 1 7
    5 4 3 2 1 7 6
    4 3 2 1 7 6 5
    3 2 1 7 6 5 4
    2 1 7 6 5 4 3
    1 7
    */
    return 0;
}