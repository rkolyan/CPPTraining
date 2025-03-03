//
// Created by rkolyan on 29.05.2024.
//


#include <string>
#include <list>
#include <iostream>
#include <sstream>

using strings = std::list<std::string>;

void parse_strings(strings &strings1, size_t &len) {
    std::string original;
    std::getline(std::cin, original, '\n');
    original.append("\n");
    std::stringstream stream(original);

    len = 0;
    bool end = false;
    size_t tmp_len = 0;
    for (std::string input1; std::getline(stream, input1, ','); ) {
        if (input1[input1.length() - 1] == '\n') {
            end = true;
            input1.erase(input1.length() - 1);
        }
        if (input1[input1.length() - 1] == ' ') {
            input1.erase(input1.length() - 1);
        }
        if (input1[0] == ' ') {
            input1.erase(0, 1);
        }
        if (!end) {
            input1.append(",");
        }
        if (input1.length() != 0) {
            std::stringstream stream2(input1);
            for (std::string input2; std::getline(stream2, input2, ' ');) {
                tmp_len = input2.length();
                if (input2[tmp_len - 1] == ',')
                    tmp_len--;
                len = tmp_len > len ? tmp_len : len;
                strings1.emplace_back(std::move(input2));
            }
        }
    }

    len = len * 3;
}

std::string format_string(const strings &strings1, const size_t &len) {
    std::string result;
    size_t count = 0;
    for (const auto &str : strings1) {
        if (count + str.length() == len || count + str.length() + 1 == len) {
            result.append(str + "\n");
            count = 0;
        } else if (count + str.length() + 1 < len) {
            result.append(str + " ");
            count += str.length() + 1;
        } else {
            result.append("\n" + str + " ");
            count = str.length() + 1;
        }
    }
    return result;
}

int main() {
    strings strings1;
    size_t len = 0;

    parse_strings(strings1, len);
    std::cout << format_string(strings1, len);

    return 0;
}