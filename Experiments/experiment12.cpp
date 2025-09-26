#include <iostream>
#include <list>

int main() {
    std::list<unsigned int> lst = {1, 2};
    std::cout << (std::prev(lst.begin()) == lst.end()) << std::endl;
    return 0;
}