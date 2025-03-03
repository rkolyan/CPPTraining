//
// Created by rkolyan on 11.04.2024.
//

#include <iostream>

size_t check_substrings_count(const std::string &str, const std::string &word) {
    size_t count = 0;
    size_t npos = str.find(word);
    while (npos != std::string::npos) {
        count++;
        npos++;
        npos = str.find(word, npos);
    }
    return count;
}

void lowercase_string(std::string &str) {
    for (char &elem : str) {
        elem = static_cast<char>(std::tolower(elem));
    }
}

int find_first_N(size_t K, size_t A_count, size_t B_count, size_t AB_count, size_t BA_count, size_t BB_count) {
    if (K == A_count)
        return 0;
    if (K == B_count)
        return 1;
    if (K == AB_count + A_count + B_count)
        return 2;
    int N = 2;
    size_t current_count = AB_count + A_count + B_count, previous_count = B_count, tmp;
    bool flag = false;
    while (current_count < K) {
        N++;
        tmp = current_count;
        if (!flag) {
            current_count += previous_count + BA_count;
        } else {
            current_count += previous_count + BB_count;
        }
        flag = !flag;
        previous_count = tmp;
    }
    if (current_count == K) {
        return N;
    }
    return -1;
}

int (void) {
    size_t A_count = 0, B_count = 0, AB_count = 0, BA_count = 0, BB_count = 0, K = 0;
    std::string A, B, word;
    std::getline(std::cin, A);
    std::getline(std::cin, B);
    std::getline(std::cin, word);
    std::cin >> K;
    lowercase_string(A);
    lowercase_string(B);
    A_count = check_substrings_count(A, word);
    B_count = check_substrings_count(B, word);
    AB_count = check_substrings_count(A + B, word) - (A_count + B_count);
    BA_count = check_substrings_count(B + A, word) - (A_count + B_count);
    BB_count = check_substrings_count(B + B, word) - (B_count + B_count);
    auto result = find_first_N(K, A_count, B_count, AB_count, BA_count, BB_count);
    if (result >= 0)
        std::cout << result << std::endl;
    else
        std::cout << "Impossible" << std::endl;
    return 0;
}