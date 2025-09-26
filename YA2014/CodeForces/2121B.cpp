#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
//SUCCESS

#define COUNTS_SIZE ('z'-'a'+1)

int main(void) {
    int t = 0, n = 0, delta = 0;
    std::string str;
    bool flag = false;
    int counts[COUNTS_SIZE];
    std::getline(std::cin, str);
    t = std::stoi(str);
    while (t) {
        std::getline(std::cin, str);
        n = std::stoi(str);
        std::getline(std::cin, str);
        std::memset(counts, 0, COUNTS_SIZE * sizeof(int));
        for (const auto &sym : str) {
            ++counts[sym - 'a'];
        }
        flag = false;
        for (int i = 1; i < n - 1; ++i) {
            delta = str[i]-'a';
            --counts[delta];
            if (counts[delta]) {
                flag = true;
                break;
            }
            ++counts[delta];
        }
        if (flag) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
        --t;
    }
    return 0;
}