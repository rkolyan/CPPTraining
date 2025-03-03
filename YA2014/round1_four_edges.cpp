//
// Created by rkolyan on 11.06.2024.
//

#include <set>
#include <iostream>

struct Node {
    int value;
    bool operator<(const Node &element) const {
        return value >= element.value;
    }
    Node() = default;
};

int main() {
    int N = 0, length = 0, p = -1;
    std::set<Node> nodes;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> length;
        nodes.insert(Node{.value = length});
    }

    int len1 = 0, len2 = 0, len3 = 0, len4 = 0;
    for (auto iter = nodes.begin(), end = std::prev(nodes.end(), 3); iter != end; iter++) {
        len1 = iter->value;
        len2 = std::next(iter)->value;
        len3 = std::next(iter, 2)->value;
        len4 = std::next(iter, 3)->value;
        if (len1 < len2+len3+len4 && !(len1 == len2 && len2 == len3 && len3 == len4)) {
            p = len1 + len2 + len3 + len4;
            break;
        }
    }
    std::cout << p;
    return 0;
}