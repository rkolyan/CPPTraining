#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> words;
    std::string word1, word2;
    int N = 0;

    std::cin >> N;
    
    for (int i = 0; i < N; ++i) {
        std::cin >> word1;
        std::cin >> word2;
        words.push_back(word1);
        words.push_back(word2);
    }
    
    // Вывод
    for (const auto& w : words) {
        std::cout << w << std::endl;
    }
    
    return 0;
}