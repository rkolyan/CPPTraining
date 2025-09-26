#include <vector>

//SUCCESS, но задача была легкая
class Solution {
public:
    int maxBalancedShipments(std::vector<int>& weights) {
        int count = 0;
        int max_weight = 0;
        bool flag = false;
        for (const auto &weight : weights) {
            if (!flag) {
                max_weight = weight;
                flag = true;
            } else if (weight >= max_weight) {
                max_weight = weight;
            } else {
                ++count;
                flag = false;
            }
        }
        return count;
    }
};