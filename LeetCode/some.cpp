#include <iostream>
#include <string>

int main() {
    std::string line, number;
    int n;
    int flag = 1;

    std::getline(std::cin, line);
    std::getline(std::cin, number);
    n = std::stoi(line);
    if (n % 11 == 0) {
        flag = 1;
        for (int i = 0; i < n; i += 11) {
            if (number[i] != '7' || number[i+1] != '9') {
                flag = 0;
                break;
            }
        }
    } else {
        flag = 0;
    }
    std::cout << flag << std::endl; // print the answer as stdout
    return 0;
}