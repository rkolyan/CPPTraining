//
// Created by rkolyan on 11.06.2024.
//

/*
#include <set>
#include <iostream>

struct Node {
    int value;
    bool operator<(const Node &element) const {
        return value >= element.value;
    }
    Node() = default;
};

int main() {
    int N = 0, length = 0, p = -1;
    std::set<Node> nodes;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> length;
        nodes.insert(Node{.value = length});
    }

    int len1 = 0, len2 = 0, len3 = 0, len4 = 0;
    for (auto iter = nodes.begin(), end = std::prev(nodes.end(), 3); iter != end; iter++) {
        len1 = iter->value;
        len2 = std::next(iter)->value;
        len3 = std::next(iter, 2)->value;
        len4 = std::next(iter, 3)->value;
        if (len1 < len2+len3+len4 && !(len1 == len2 && len2 == len3 && len3 == len4)) {
            p = len1 + len2 + len3 + len4;
            break;
        }
    }
    std::cout << p;
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using count_t = unsigned int;
using number_t = unsigned int;
using sum_t = int;

//SUCCESS

/*
Идея:
1)В начале упорядочиваем палочки по длине в обратном порядке
2)Далее смотрим слева направо
3)Если сумма 3-х справа < 1 слева, пропускаем
4)Частный случай: ромб - не может быть невыпуклым (a[0] != a[3])
*/

sum_t find_max_perimetr_nonconvex(const std::vector<number_t> &a) {
    sum_t sum = -1;
    sum_t tmp_sum = -1;
    if (a.size() > 3) {
        for (unsigned int i = 0; i < a.size()-3; i++) {
            if (a[i] != a[i+3]) {
                tmp_sum = a[i+1] + a[i+2] + a[i+3];
                if (tmp_sum > a[i]) {
                    sum = a[i] + tmp_sum;
                    break;
                }
            }
        }
    }
    return sum;
}

int main(void) {
    count_t N = 0;
    number_t input_num = 0;
    std::vector<number_t> a;
    std::multiset<number_t, std::greater<number_t>> a_input;

    std::cin >> N;
    for (unsigned int i = 0; i < N; i++) {
        std::cin >> input_num;
        a_input.emplace(input_num);        
    }
    a.resize(N);
    std::copy(a_input.cbegin(), a_input.cend(), a.begin());
    std::cout << find_max_perimetr_nonconvex(a);
    /*
        Идея следующая
        4 палочки можно соотнести друг с другом,
        Если из 2х пар можно построить одинаковую сторону -> мы можем построить 4х угольник
        А как доказать, что из этого 4х угольника можно впуклый?

    */
    return 0;
}