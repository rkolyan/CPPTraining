#include <map>
#include <vector>
#include <iostream>
#include <list>

using namespace std;


using card_t = int;
using pos_t = unsigned int;
using diff_t = unsigned int;

class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        std::map<card_t, pos_t> cards_poses;
        diff_t min_diff = cards.size();
        pos_t pos = 1;
        for (const auto &card : cards) {
            auto &cur_pos = cards_poses[card];
            if (cur_pos)
                min_diff = std::min(min_diff, pos - cur_pos);
            cur_pos = pos;
            pos++;
        }
        if (min_diff < cards.size()) {
            return min_diff;
        }
        return -1;
    }

    struct Node{
        std::map<int, Node *> map;
        Node *&operator[](int index) {
            return map[index];
        }
    };
    


    int countDistinct(vector<int>& nums, int k, int p) {
        std::vector<Node*> nodes(nums.size());
        std::list<unsigned int> lst;
        Node *root = new Node();
        int curr_k = 0, curr_begin = 0, curr_end = 0;
        int count = 0;
        for (unsigned int i = 0; i < nums.size(); ++i) {
            if ((nums[i] / p) * p == nums[i]) {
                lst.push_back(i);
            }
        }
        if (lst.size() > k) {
            //TODO
        } else {
            std::fill(nodes.begin(), nodes.end(), root);
            for (unsigned int i = 0; i < nums.size(); ++i) {
                const auto &num = nums[i];
                for (unsigned int j = 0; j <= i; ++j) {
                    auto &node_ptr = nodes[j];
                    auto &node = (*node_ptr)[num];
                    if (!node) {
                        node = new Node();
                        count++;
                        node_ptr = node;
                    }
                }
            }   
        }
        //TODO: Надо удалить дерево
        return count;
    }
};

int main() {
    //[2, 3, 3, 2], [2, 3, 3], [2, 3], [2], [3, 3, 2], [3, 3], [3] - вроде правильно, но только в случае
    std::vector<int> nums {2,3,3,2};
    std::cout << Solution().countDistinct(nums, 2, 2);
}