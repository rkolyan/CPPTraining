//
// Created by rkolyan on 27.01.2025.
//

#include <iostream>

int main(void) {
    unsigned int a = 0, b = 0, c = 0, a_c = 0, b_c = 0, c_c = 0;
    std::cin >> a >> b >> c >> a_c >> b_c >> c_c;
    //TODO: Странное условие...
    //1)Снимаем из 2-й и 3-й пачки всю возможную на обмен сумму (a_count = a / a_c, оставляем a = a - a_count * a_c, снимаем b = b - b_count * b_c, c = c + (a_count + b_count) * c_c)

    return 0;
}