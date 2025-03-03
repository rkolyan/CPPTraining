//
// Created by rkolyan on 04.06.2024.
//

#include <set>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

int main() {
    std::set<std::string> winners, losers;
    std::string win1, lose1, tmp;
    std::stringstream sstream;
    unsigned int N = 0;
    std::cin >> N;
    std::cin.ignore(256, '\n');

    for (N >>= 1; N > 0; N >>= 1) {
        for (unsigned int i = 0; i < N; i++) {
            std::getline(std::cin, tmp);
            sstream.str(tmp);
            sstream.seekg(0);
            std::getline(sstream, win1, ' ');
            std::getline(sstream, lose1, ' ');
            if (losers.find(win1) == losers.end()) {
                winners.insert(win1);
            }
            winners.erase(lose1);
            losers.insert(lose1);
        }
    }

    std::cout << *(winners.begin());
    return 0;
}