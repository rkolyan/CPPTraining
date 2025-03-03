#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

bool compare(char a, char b) {
    return a > b;
}

unsigned int f(unsigned int sum, const std::vector<unsigned int> &numbers, unsigned int index) {
    if (index == numbers.size())
        return sum;
    //Прибавить к сумме значение
    sum += numbers[index];
    //Создать из неё строку
    std::string sum_str = std::to_string(sum);
    //Создать стек индексов и заполнить его
    std::list<unsigned int> index_stack;
    std::vector<bool> flags;
    flags.resize(sum_str.size(), false);
    for (unsigned int i = 0; i < sum_str.size(); i++) {
        index_stack.push_front(i);
        flags[i] = true;
    }

    unsigned int max_sum = 0, new_sum = 0, final_sum = 0, dec = 1, pos = 0;
    bool begin = false;
    while (!index_stack.empty()) {

        //Создание новой суммы
        dec = 1;
        new_sum = 0;
        for (const auto &ind : index_stack) {
            new_sum += (sum_str[ind] - '0') * dec;
            dec *= 10;
        }

        //Вычислить новую сумму
        final_sum = f(new_sum, numbers, index + 1);
        if (final_sum > max_sum)
            max_sum = final_sum;

        begin = false;
        do {
            if (begin) {
                pos = 0;
            } else {
                pos = index_stack.front();
                flags[pos] = false;
                pos++;
                index_stack.pop_front();
            }
            for (; pos < sum_str.size(); pos++) {
                if (!flags[pos]) {
                    flags[pos] = true;
                    index_stack.push_front(pos);
                    break;
                }
            }
            if (pos < sum_str.size())
                begin = true;
        } while (!index_stack.empty() && index_stack.size() < sum_str.size());
    }
    return max_sum;
}

int main(void) {
    unsigned int N = 0, sum = 0;
    std::vector<unsigned int> numbers;

    std::cin >> N;
    numbers.resize(N);


    for (unsigned int i = 0; i < N; i++) {
        std::cin >> numbers[i];
    }

    std::cout << f(0, numbers, 0);
    return 0;
}