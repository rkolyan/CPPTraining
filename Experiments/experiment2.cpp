//
// Created by rkolyan on 17.01.2025.
//

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string A = "pospospospospos";
    std::string B = "pospos";

    std::regex re(B);
    std::sregex_iterator it(A.begin(), A.end(), re);
    std::sregex_iterator end;

    int count = 0;
    while (it != end) {
        ++count;
        it++;
    }

    std::cout << "Количество вхождений подстроки B в строке A: " << count << std::endl;

    return 0;
}
