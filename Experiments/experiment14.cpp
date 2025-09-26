#include <unordered_map>
#include <string>
#include <iostream>

int main(void) {
    std::unordered_multimap<std::string, int> map_str;
    map_str.reserve(10);
    map_str.emplace("lo", 1);
    map_str.emplace("lo", 2);
    for (const auto &element : map_str) {
        std::cout << element.first << ' ' << element.second << std::endl;
    }
    std::cout << "multimap.size() == " << map_str.size() << std::endl;
    map_str.extract("lo");
    std::cout << "multimap.size() == " << map_str.size() << std::endl;
    map_str.emplace("lo", 10);
    auto iter = map_str.find("lo");
    std::cout << (*iter).second << std::endl;
    map_str.erase(iter);
    iter = map_str.find("lo");
    std::cout << (*iter).second << std::endl;
    return 0;
}