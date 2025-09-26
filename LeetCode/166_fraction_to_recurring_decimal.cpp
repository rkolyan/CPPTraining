#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <memory>
#include <iostream>

//SUCCESS, правда по скорости 3 ms, ой, да пошли они нахер, эти супероптимизаторы, шарящие за скорость, я сделал то же самое, только я паралелльно видосик смотрел, главное написать, блиа
/*
Вот самое быстрое решение за 0 ms
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0"; // Zero numerator gives "0"

        string result;

        // Handle negative sign
        if ((numerator < 0) ^ (denominator < 0)) 
            result += '-';

        // Convert to long long to avoid overflow
        long long n = abs((long long)numerator);
        long long d = abs((long long)denominator);

        // Append integer part
        result += to_string(n / d);
        long long remainder = n % d;
        if (remainder == 0) return result; // No fractional part

        result += '.'; // Start fractional part

        // Map to store remainder and its corresponding index in result
        unordered_map<long long, int> remainderIndex;

        while (remainder != 0) {
            // If this remainder has been seen before, we have a repeating cycle
            if (remainderIndex.count(remainder)) {
                result.insert(remainderIndex[remainder], "(");
                result += ')';
                break;
            }

            // Store the current remainder with its position
            remainderIndex[remainder] = result.size();

            remainder *= 10;
            result += to_string(remainder / d);
            remainder %= d;
        }

        return result;
    }
};
*/

template<typename T>
class StackAllocator : public std::allocator<T>{
private:
    char* buffer_;
    size_t size_;
    size_t offset_;
    
public:
    using value_type = T;
    
    StackAllocator(char* buffer, size_t size) 
        : buffer_(buffer), size_(size), offset_(0) {}
    
    template<typename U>
    StackAllocator(const StackAllocator<U>& other)
        : buffer_(other.buffer_), size_(other.size_), offset_(other.offset_) {}
    
    T* allocate(size_t n) {
        size_t required_size = n * sizeof(T);
        size_t aligned_offset = (offset_ + alignof(T) - 1) & ~(alignof(T) - 1);
        
        if (aligned_offset + required_size > size_) {
            throw std::bad_alloc();
        }
        
        T* ptr = reinterpret_cast<T*>(buffer_ + aligned_offset);
        offset_ = aligned_offset + required_size;
        return ptr;
    }
    
    void deallocate(T* p, size_t n) noexcept {
        // В стековом аллокаторе деаллокация обычно не делается
        // или делается только для последнего выделенного блока
    }
    
    template<typename U>
    struct rebind {
        using other = StackAllocator<U>;
    };
    
    char* buffer() const { return buffer_; }
    size_t size() const { return size_; }
    size_t offset() const { return offset_; }
    void reset() { offset_ = 0; }
};

// Сравнение аллокаторов
template<typename T, typename U>
bool operator==(const StackAllocator<T>&, const StackAllocator<U>&) {
    return true; // Все стековые аллокаторы считаются равными
}

template<typename T, typename U>
bool operator!=(const StackAllocator<T>& a, const StackAllocator<U>& b) {
    return !(a == b);
}

class Solution {
public:
    std::string fractionToDecimal(int numerator, int denominator) {
        /*
        Итак, нужно определить
        4/333 = 0.(400/333) = 0.0(
        Алгоритм возможно следующий:
        первое число = 
        */
        if (!numerator) {
            return "0";
        }
        constexpr size_t BUFFER_SIZE = 2 << 13, MINI_BUFFER_SIZE = 16;
        char buffer1[MINI_BUFFER_SIZE], buffer2[BUFFER_SIZE];
        char buffer3[(sizeof(long) + sizeof(int)) * BUFFER_SIZE];
        
        StackAllocator<char> allocator1(buffer1, MINI_BUFFER_SIZE), allocator2(buffer2, BUFFER_SIZE);
        StackAllocator<std::pair<const long,int>> allocator3(buffer3, BUFFER_SIZE);
        std::vector<char, StackAllocator<char>> num(allocator1);
        std::string syms(allocator2);
        std::unordered_map<long, int> table(allocator3);
        table.reserve(BUFFER_SIZE);

        num.reserve(16);
        syms.reserve(BUFFER_SIZE);
        long lnumerator = numerator, ldenominator = denominator;
        if (numerator < 0 && denominator > 0 || numerator > 0 && denominator < 0) {
            lnumerator = std::abs(lnumerator);
            ldenominator = std::abs(ldenominator);
            syms.push_back('-');
        }
        long remind = lnumerator / ldenominator;
        int index = 0;
        auto table_iter = table.begin();
        do {
            num.push_back(remind % 10);
            remind /= 10;
        } while (remind);
        while (!num.empty()) {
            syms.push_back(num.back()+'0');
            num.pop_back();
        }
        remind = lnumerator % ldenominator;
        //Сохраняем значение numeratora
        if (remind) {
            syms.push_back('.');
            index = syms.size();
            while (remind) {
                table_iter = table.find(remind);
                if(table_iter != table.end()) {
                    syms.insert(syms.begin() + (*table_iter).second, '(');
                    syms.push_back(')');
                    break;
                }
                table.emplace(remind, index);
                ++index;
                remind *= 10;
                syms.push_back('0' + remind / ldenominator);
                remind = remind % ldenominator;
            }
        }
        std::string result(syms);
        return result;
        /*
        Итак, как запомнить что дробь повторяется? Для этого можно хранить отдельно значение numerator для каждого разряда
        Допустим, 3/444
        10/3 = 3.(3)

        */
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::cout << sol.fractionToDecimal(1, 2) << std::endl;
    std::cout << sol.fractionToDecimal(2, 1) << std::endl;
    std::cout << sol.fractionToDecimal(4, 333) << std::endl;
    std::cout << sol.fractionToDecimal(150, 900) << std::endl;
    std::cout << sol.fractionToDecimal(-150, 900) << std::endl;
    std::cout << sol.fractionToDecimal(0, 1) << std::endl;
    std::cout << sol.fractionToDecimal(1, -1) << std::endl;
    std::cout << sol.fractionToDecimal(-1, 1) << std::endl;
    return 0;
}