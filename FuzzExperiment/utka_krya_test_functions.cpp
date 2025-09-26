#include <vector>
#include <map>

using count_t = unsigned int;
using number_t = unsigned int;

unsigned int utka_krya_brute_force(const std::vector<unsigned int> &array) {
    unsigned int diff = 0;
    std::map<number_t, count_t> ducks;

    for (const auto &elem : array) {
        ducks[elem]++;
    }
    return diff;
}