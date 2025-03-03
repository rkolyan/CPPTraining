//
// Created by rkolyan on 27.01.2025.
//

#include <iostream>
#include <regex>

int main(void) {
    int N = 0;
    std::size_t position = 0, length = 0, count = 0;
    std::string str, colors, tmp;
    std::cin >> N;
    std::cin.ignore();
    std::getline(std::cin, str);
    std::getline(std::cin, colors);
    std::regex regex("\\w+"), regex2(R"(BB|YY)");
    //1)Находим позицию первого слова
    auto begin = std::sregex_iterator {str.begin(), str.end(), regex};
    auto end = std::sregex_iterator();
    position = 0;
    for (auto iter = begin; iter != end; iter++) {
        position = iter->position();
        length = (*iter).length();
        //std::cout << position;
        tmp = colors.substr(position, length);
        if (std::regex_search(tmp, regex2)) {
            count++;
        }
        //std::cout << tmp;
    }
    std::cout << count;
    return 0;
}