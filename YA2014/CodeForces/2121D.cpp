#include <iostream>
#include <vector>

int main(void) {
    std::vector<int> a, b;
    std::size_t n, t;
    a.reserve(40);
    b.reserve(40);
    for (std::cin >> t; t; --t) {
        std::cin >> n;
        a.resize(n);
        b.resize(n);
        for (auto &element : a) {
            std::cin >> element;
        }
        for (auto &element : b) {
            std::cin >> element;
        }
        /*
        Нужно сделать a_i < a_{i+1}, b_i < b_{i+1}, a_i < b_i
        Мы соответственно можем осуществлять только 3 операции, поменять a_i <-> a_{i+1}, b_i <-> b_{i+1}, a_i <-> b_i
        Ну, допустим мы отсортировали
        */
    }
    return 0;
}