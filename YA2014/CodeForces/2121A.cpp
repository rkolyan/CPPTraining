#include <iostream>
#include <vector>
#include <climits>

//SUCCESS

int main(void) {
    int t = 0, n = 0, s = 0, tmp;
    int min_num = INT_MAX, max_num = INT_MIN;
    std::cin >> t;
    while (t) {
        std::cin >> n >> s;
        min_num = INT_MAX;
        max_num = INT_MIN;
        for (int i = 0; i < n; ++i) {
            std::cin >> tmp;
            if (min_num > tmp) {
                min_num = tmp;
            }
            if (max_num < tmp) {
                max_num = tmp;
            }
        }
        if (s <= min_num) {
            std::cout << max_num - s << std::endl;;
        } else if (s >= max_num) {
            std::cout << s - min_num << std::endl;
        } else {
            std::cout << max_num - min_num + std::min(s - min_num, max_num - s) << std::endl;
        }
        --t;
    }
    return 0;
}