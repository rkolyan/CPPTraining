#include <iostream>
#include <vector>

//TODO: Задача херня, почему количество пар = количеству простых чисел?
//TODO: Надо проверить перебором
int main() {
    unsigned int N = 0, M = 0, begin = 0;
    unsigned long long count = 0;
    std::vector<unsigned int> nums;    
    nums.resize(10000000, 1);
    nums[1] = 2;
    for (unsigned int index = 1; index < 10000000;) {
        auto delta = nums[index];
        for (unsigned int jndex = index + delta; jndex < 10000000; jndex += delta) {
            nums[jndex] = 0;
        }
        index++;
        while (!nums[index]) {
            index++;
        }
    }

    std::cin >> N;
    for (unsigned int i = 0; i < )
    return 0;
}