#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

int main(void) {
    int N = 0, Q = 0, operation = 0, parameter;
    long double middle = 0, sum = 0, diff = 0, result = 0;
    std::vector<long double> arr;
    std::vector<long double> sums;

    std::cin >> N;
    std::cin >> Q;

    arr.reserve(N + Q);
    arr.resize(N);
    std::cout << std::fixed;            // Фиксированный формат (не научная нотация)
    std::cout << std::setprecision(7);  // 7 знаков после точки
    for (auto &element : arr) {
        std::cin >> element;
    }

    for (unsigned int i = 0; i < Q; i++) {
        std::cin >> operation >> parameter;
        switch (operation)
        {
        case 1:
            /* Посчитать отклонение последних parameter элементов */
            middle = 0, sum = 0, diff = 0, result = 0;
            for (int i = arr.size() - 1, end = arr.size() - parameter - 1; i > end; --i) {
                middle += arr[i];
            }
            middle /= parameter;
            for (int i = arr.size() - 1, end = arr.size() - parameter - 1; i > end; --i) {
                diff = arr[i] - middle;
                sum += diff * diff * diff;
            }
            result = cbrt(sum / parameter);
            std::cout << result << std::endl;
            break;
        default:
            arr.push_back(parameter);
            break;
        }
    }
    /*
    Алгоритм подсчета следующий
    Итак, алгоритм вычисления следующий
    */
    return 0;
}