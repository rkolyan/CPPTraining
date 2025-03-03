//
// Created by rkolyan on 17.01.2025.
//

#include <string>
#include <iostream>
#include <regex>


class BigNum {
public:
    BigNum(int num);
    BigNum &operator+=()

private:
    int arr[3000];
};

int find_fibonachi(int arr[3000], int n) {
    int arr1[3000] = {0};

    if (n > 2) {
        arr1[0];
    } else if (n == 1 || n == 2) {
        arr[0] = 1;
    } else {
        arr[0] = 0;
    }
}

int main(void) {
    std::string A, B, S, K, AB, BA, BB;
    int K_count = 0, A_count = 0, B_count = 0, AB_count = 0, BA_count = 0, BB_count = 0;

    std::getline(std::cin, A);
    std::getline(std::cin, B);
    std::getline(std::cin, S);
    std::getline(std::cin, K);
    AB = A + B;
    BA = B + A;
    BB = B + B;
    K_count = std::stoi(K);

    //Захватить
    std::regex regex(S);
    A_count = std::distance(std::sregex_iterator(A.begin(), A.end(), regex), std::sregex_iterator());
    B_count = std::distance(std::sregex_iterator(B.begin(), B.end(), regex), std::sregex_iterator());
    AB_count = std::distance(std::sregex_iterator(AB.begin(), AB.end(), regex), std::sregex_iterator());
    BA_count = std::distance(std::sregex_iterator(BA.begin(), BA.end(), regex), std::sregex_iterator());
    BB_count = std::distance(std::sregex_iterator(BB.begin(), BB.end(), regex), std::sregex_iterator());



    return 0;
}