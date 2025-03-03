//
// Created by rkolyan on 06.06.2024.
//

#include <map>
#include <iostream>

using count_t = unsigned int;
using number_t = unsigned int;

int main() {
    unsigned int N = 0, tmp = 0;
    std::map<number_t, count_t> ducks;

    std::cin >> N;

    //Упорядочиваем элементы в обратном порядке, при этом подсчитывая их количество
    for (unsigned int i = 0; i < N; i++) {
        std::cin >> tmp;
        ducks[tmp]++;
    }

    //TODO: Создать дерево минимальных разностей между соседними сверху элементами
    //Алгоритм следующий

    return 0;
}