#include <vector>
#include <iostream>

std::string createBitString(int n, int k) {
    /*
    Нужно создать строку из подстрок 010 и 101
    Так, в чем прикол
    Ну допустим
    есть число 1010
    А 0110 - тут тоже 2 подстроки 010 и 101
    Я так понял без разницы, просто создаём люьую строку
    */
    std::string str;
    str.reserve(n);
    for (int i = 0; i < k; ++i) {
        str.push_back('1');
    }
    for (int i = k; i < n; ++i) {
        str.push_back('0');
    }
    return str;
}

int main(void) {
    int t = 0;
    int n = 0, k = 0;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        std::cout << createBitString(n, k) << std::endl;
    }
    return 0;
}