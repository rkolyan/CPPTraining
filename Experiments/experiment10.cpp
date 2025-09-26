#include <vector>
#include <set>
#include <iostream>

using number_t = unsigned int;

int main(void) {
    std::vector<number_t> numbers = {1, 2, 3, 1, 4, 1, 3};
    std::multiset<number_t> mset;
    mset.insert(numbers.cbegin(), numbers.cend());
    std::cout << mset.count(4) << std::endl;
    auto element = mset.extract(4);
    std::cout << element.value() << std::endl;;
    std::cout << mset.count(4) << std::endl;

    std::multiset<number_t> mset2 = {2};
    std::cout << mset2.size() << std::endl;
    mset2.extract(2);
    std::cout << mset2.size() << std::endl;
    mset2.extract(5);
    std::cout << mset2.size() << std::endl;

    std::multiset<number_t> mset3 = {2, 2};
    std::cout << mset3.size() << std::endl;
    mset3.extract(2);
    std::cout << mset3.size() << std::endl;
    return 0;
}