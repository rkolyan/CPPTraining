#include <iostream>
#include <vector>

using number_t = unsigned int;
using position_t = unsigned long;

#define MAX_SIZE 500

bool is_exit(const std::vector<position_t> &positions, const std::vector<position_t> &begins, const std::vector<number_t> &delays, int k) {
    /*
    Итак, тут явно нужно
    Если представить координатую плоскость с абсциссой p и ординатой t, то автомобиль будет двигаться либо по прямой y = x, либо, если столкнется со светофором, y = -x
    Таким образом,проводим через каждый светофор прямую y = x и y = -x
    Итак, delays - если delays > y, при x < 10^15, то
    
    Итак, мы имеем begins - это -b и мы находимся на прямой y = x + b, где = b = -begin[i]
    при этом, у нас каждая красная позиция задаётся на прямой delay + l*k = position + b => b = delay - position + l*k, где l - неотрицательный целочисленный параметр

    y = x + delay - position + l*k
    y = x - begin

    Проходим по каждой позиции, и если это точка достижима из какой-нибудь begins, то ставим как переломную точку для begin, больше её на этом проходе нельзя занимать
    Далее, если после прохода у точки нет перелома, то она вышла из отрезка
    Далее, проходимся в обратном порядке, также
    После прохода точки кладём в одну из очередей 
    Причём наверное, стоит сами позиции положить в 
    */
}

int main(void) {
    int t = 0;
    int n = 0, k = 0, q = 0;
    std::vector<position_t> p, a;
    std::vector<number_t> d;
    std::cin >> t;
    p.reserve(MAX_SIZE);
    d.reserve(MAX_SIZE);
    a.reserve(MAX_SIZE);
    while (t--) {
        std::cin >> n >> k;
        p.resize(n);
        d.resize(n);
        for (auto &position : p) {
            std::cin >> position;
        }
        for (auto &delay : d) {
            std::cin >> delay;
        }
        std::cin >> q;
        a.resize(q);
        for (auto &element : a) {
            std::cin >> element;
        }
    }
    return 0;
}