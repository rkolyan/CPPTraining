#include <type_traits>
#include <limits>
#include <cmath>
#include <iostream>

template <typename T>
constexpr size_t max_digits() {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    
    constexpr T max_value = std::numeric_limits<T>::max();
    size_t digits = 0;
    T n = max_value;
    do {
        n /= 10;
        ++digits;
    } while (n != 0);
    
    return digits;
}

int main() {
    std::cout << "int: " << max_digits<int>() << std::endl;          // 10 (для 32-битного int)
    std::cout << "unsigned int: " << max_digits<unsigned int>() << std::endl;  // 10
    std::cout << "long long: " << max_digits<long long>() << std::endl;       // 19 (для 64-битного)
    std::cout << "char: " << max_digits<char>() << std::endl;        // 3 (если char 8-битный знаковый)
    
    return 0;
}