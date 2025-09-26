#include <iostream>

int main(void) {
    unsigned int T = 0, N = 0;
    unsigned int minimum = 1000000001, maximum = 0, tmp = 0, d = 0, res1 = 0, res2 = 0;

    /*
    (a + d )/ (b + d) = c
    a > b
    1 + (a - b) / (b + d) = c
    1 + (3 - 1) / (1 + d) = c
    */
    std::cin >> T;
    for (unsigned int i = 0; i < T; i++) {
        std::cin >> N;
        minimum = 1000000001;
        maximum = 0;
        for (unsigned int j = 0; j < N; j++) {
            std::cin >> tmp;
            maximum = std::max(tmp, maximum);
            minimum = std::min(tmp, minimum);
        }
        d = 1;
        
        
        while((maximum - minimum) % (minimum + d)) {
            d++;
        }
        std::cout << d << std::endl;
    }
    return 0;
}