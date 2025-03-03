//
// Created by rkolyan on 05.06.2024.
//

#include <iostream>
#include <regex>

//SUCCESS

int main() {
    std::regex before(R"(\([a-zA-Z]+\)|[^a-zA-Z0-9() ]\))");
    std::string input, output;

    std::getline(std::cin, input);
    output = std::regex_replace(input, before, "<S>$&</S>");
    std::cout << output;
}