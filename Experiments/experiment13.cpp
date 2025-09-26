#include <set>
#include <vector>
#include <iostream>
#include <list>

std::string countAndSay(int n) {
    std::string str{"1"};
    char cur_sym = '1';
    unsigned int count = 0;
    std::list<std::string> syms;
    for (unsigned int i = 1; i < n; i++) {
        syms.clear();
        cur_sym = '1';
        count = 0;
        for (const auto& sym : str) {
            if (sym == cur_sym) {
                count++;
            } else {
                if (count > 0) {
                    syms.push_back(std::to_string(count));
                    syms.push_back(std::string{cur_sym});
                }
                cur_sym = sym;
                count = 1;
            }
        }
        if (count > 0) {
            syms.push_back(std::to_string(count));
            syms.push_back(std::string{cur_sym});
        }
        str.clear();
        for (const auto& element : syms) {
            str += element;
        }
    }
    return str;
}

int main(void) {
    std::multiset<unsigned int> mset = {1, 4, 2, 2, 33, 3, 3, 3, 5};
    std::multiset<unsigned int> mset2;
    std::vector<unsigned int> result;
    for (auto &element : mset) {
        mset2.insert(element * 2);
    }
    result.resize(std::distance(mset2.begin(), mset2.end()));
    std::copy(mset2.begin(), mset2.end(), result.begin());
    for (const auto &element : result) {
        std::cout << element << std::endl;
    }
    std::cout << result.size() << std::endl;
    std::cout << std::string{'a'} << std::endl;
    std::string str{'a'};
    str += "abc";
    std::cout << str << std::endl;
    str.clear();
    str += "bac";
    std::cout << str << std::endl;
    std::cout << countAndSay(4);
    return 0;
}