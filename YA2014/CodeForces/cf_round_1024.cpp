#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <climits>

//A SUCCESS
std::optional<std::vector<unsigned int>> LRC_AND_VIP(const std::vector<unsigned int> &nums) {
    /*
    Итак, чтобы gcd не были равными, надо, находи
    Тут намек на жадный алгоритм
    Итак, нам для последовательности нужно просто найти число Ai, для которого gcd(A1, A2,..,Ai-1,Ai+1,...,AN) != Ai
    Допустим, не нашли такого числа
    Пример:
    1 20 51 9
    Короче, прикол, если gcd(A1, A2,..., Ai,..., AN) = 1, то gcd(A1, A2,..,Ai-1,Ai+1,...,AN) != Ai в любом случае, иначе бы у нас не было бы
    Если gcd(A1, ..., AN) = B, то как разделить меж собой? Попробуем взять сразу наибольшее из чисел и вложить в другую последовательность (можно сразу все такие числа взять),
    тогда, если gcd(A1,...,AK) = gcd(Ak+1,...,AN) = AMAX, то все элементы одинаковы, отвечаем NO

    */
    unsigned int max_num = nums.front();
    bool differ_flag = false;
    for (const auto &element : nums) {
        if (element != max_num) {
            differ_flag = true;
            if (element > max_num) {
                max_num = element;
            }
        }
    }
    if (differ_flag) {
        std::vector<unsigned int> result(nums.size(), 1);
        for (unsigned int i = 0; i < nums.size(); ++i) {
            if (nums[i] == max_num) {
                result[i] = 2;
            }
        }
        return result;
    }
    return {};
}

/*
int main(void){
    unsigned int t = 0, n = 0, input_num;
    std::vector<unsigned int> nums;

    std::cin >> t;
    for (auto ti = 0; ti < t; ++ti) {
        std::cin >> n;
        nums.reserve(n);
        nums.clear();
        for (unsigned int i = 0; i < n; ++i) {
            std::cin >> input_num;
            nums.push_back(input_num);
        }
        auto result = LRC_AND_VIP(nums);
        if (result.has_value()) {
            std::cout << "Yes" << std::endl;
            for (const auto &element : result.value()) {
                std::cout << element << ' ';
            }
            std::cout << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }
    return 0;
}
*/

//B
enum who_won_t {
    TOM_WON,
    JERRY_WON
};

who_won_t apple_game(const std::vector<unsigned int> apples, unsigned int k) {
    /*
        Итак, каждый игрок играет оптимально, это значит, что текущий игрок должен знать все ходы наперёд, в том числе выгодные для противника
        Итак, игрок который делает ход для себя не должен допустить max - min > k
        Вроде задача тоже простая, здесь надо просто посчитать, сколько яблок всего и рассмотреть крайние ситуации, где max - min > k остаются в результате первого хода
        1)Находим минимум в массиве
        2)Далее, находим количество элементов разность которых с минимумом больше k
        3)Если таких элементов несколько -> Джерри выиграл
        4)Если один и он > k+1 -> Джерри выиграл
        5)В иных случая считаем четность, если количество яблок нечётно, то Джерри выиграл, если четно - Том выиграл
    */
    unsigned int minimum = UINT_MAX;
    unsigned int sum = 0;
    unsigned int max_differ = 0;
    unsigned int max_count = 0;
    unsigned int differ = 0;
    for (const auto &apple : apples) {
        if (minimum > apple) {
            minimum = apple;
        }
        sum += apple;
    }
    for (const auto &apple : apples) {
        differ = apple - minimum;
        if (differ > k) {
            ++max_count;
            max_differ = std::max(differ - k, max_differ);
        }
    }
    if (max_count > 1 || max_differ > 1 || !(sum & 1)) {
        return JERRY_WON;
    }
    return TOM_WON;
}

int main(void){
    unsigned int t = 0, n = 0, k = 0, input_num;
    std::vector<unsigned int> nums;

    std::cin >> t;
    for (auto ti = 0; ti < t; ++ti) {
        std::cin >> n >> k;
        nums.reserve(n);
        nums.clear();
        for (unsigned int i = 0; i < n; ++i) {
            std::cin >> input_num;
            nums.push_back(input_num);
        }
        auto result = apple_game(nums, k);
        switch (result)
        {
        case TOM_WON:
            std::cout << "Tom" << std::endl;
            break;
        default:
            std::cout << "Jerry" << std::endl;
        }
    }
    return 0;
}