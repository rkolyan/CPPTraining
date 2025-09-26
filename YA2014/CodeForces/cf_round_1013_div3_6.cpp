#include <iostream>
#include <vector>
#include <cmath>

unsigned int find_paths_count(const std::vector<std::string> &hooks, unsigned int N, unsigned int M, unsigned int d) {
    std::vector<std::vector<unsigned int>> counts;
    std::vector<unsigned int> tmp;
    counts.resize(N, std::vector<unsigned int>(M));
    auto &first_str = hooks[hooks.size() - 1];
    auto &first_array = counts[0];
    for (unsigned int i = 0; i < first_str.size(); i++) {
        switch (first_str[i])
        {
        case '#':
            first_array[i] = 1;
            break;
        
        default:
            first_array[i] = 0;
        }
    }
    unsigned int curr_i = 1;
    for (auto str_iter2 = hooks.crbegin(), str_iter1 = std::next(str_iter2); str_iter1 != hooks.crend(); ++str_iter1, ++str_iter2, ++curr_i) {
        for (unsigned int j = 0; j < (*str_iter1).size(); j++) {
            switch ((*str_iter1)[j])
            {
            case '#':
                //TODO: Проверяем все значения снизу и слева
                //TODO: Сначала снизу, только есть одна проблема - нельзя больше 2х раз касаться руками на уровне, значит придётся использовать жадный алгоритм?
                //TODO: Берём 
                for (unsigned i_r = curr_i - 1; i_r < )
                break;
            
            default:
                break;
            }
        }
    }
}

int main(void) {
    unsigned int T = 0, N = 0, M = 0, D = 0, R;
    std::string str;
    std::cin >> T;
    std::vector<std::string> hooks;

    for (unsigned int i = 0; i < T; i++) {
        std::cin >> N >> M >> D;
        hooks.resize(N);
        for (auto &str : hooks) {
            std::cin >> str;
        }
    }
    return 0;
}