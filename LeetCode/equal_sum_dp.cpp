#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <numeric>

bool canPrediction(std::vector<unsigned int> &nums) {
    unsigned int full_sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (full_sum % 2)
        return false;
    full_sum = full_sum / 2;
    std::set<unsigned int> sums = {0};
    std::list<unsigned int> cur_sums;
    unsigned int tmp_sum = 0;
    for (const auto &element : nums) {
        for (const auto &sum : sums) {
            tmp_sum = element + sum;
            if (tmp_sum == full_sum) {
                return true;
            }
            cur_sums.push_back(sum + element);
        }
        sums.insert(cur_sums.begin(), cur_sums.end());
        cur_sums.clear();
    }
    /*
    Итак, f(A, s1) -> 
        f(A/a1, s)
        f(A/a1, s + a1)
    Для каждого
    */
    return false;
}

int main(void) {
    unsigned int N = 0;
    std::vector<unsigned int> nums;

    std::cin >> N;

    nums.resize(N);

    for (auto &element : nums) {
        std::cin >> element;
    }

    std::cout << canPrediction(nums) << std::endl;
}