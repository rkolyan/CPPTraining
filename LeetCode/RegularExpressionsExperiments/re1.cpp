#include <regex>
#include <iostream>

int main(void) {
    std::regex re1(R"(R\d+C\d+)"), re_number(R"(\d+)"), re_word(R"([A-Z]+)");
    std::string str;
    constexpr auto mult = 'Z' - 'A' + 1;
    unsigned int N = 0;
    std::cin >> N;
    std::getline(std::cin, str);
    for (unsigned int i = 0; i < N; i++) {
        std::getline(std::cin, str);
        if (std::regex_match(str, re1)) {
            std::sregex_iterator iter(str.begin(), str.end(), re_number);
            auto row = (*(iter++)).str();
            auto column_num = std::stoi((*(iter)).str());
            std::string column;
            do {
                auto tmp = 'A' - 1 + column_num % mult;
                if (tmp >= 'A') 
                    column.push_back(tmp);
                column_num /= mult;
            } while (column_num != 0);
            std::reverse(column.begin(), column.end());
            std::cout << column << row << std::endl;
        } else {
            std::sregex_iterator iter1(str.begin(), str.end(), re_word);
            std::sregex_iterator iter2(str.begin(), str.end(), re_number);
            std::string column {(*iter1).str()};
            std::string row {(*iter2).str()};
            int column_num = 0;
            for (const auto &symbol : column) {
                column_num *= mult;
                column_num += symbol - 'A' + 1;
            }
            std::cout << 'R' << row << 'C' << column_num << std::endl;
        }
    }
}