//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <set>

struct Node {
    int width;
    int height;
    bool operator<(const Node &element) const {
        return width > element.width || width == element.width && height > element.height;
    }
    Node() = default;
};

int main() {
    unsigned int N = 0;
    Node node{};
    std::set<Node> set;
    std::cin >> N;
    bool chaos = false;
    for (unsigned int i = 0; i < N; i++) {
        std::cin >> node.width >> node.height;
        if (node.width < node.height) {
            std::swap(node.width, node.height);
        }
        if (set.find(node) != set.end()) {
            std::swap(node.width, node.height);
            if (set.find(node) != set.end()) {
                chaos = true;
                break;
            }
        }
        set.insert(node);
    }
    if (!chaos) {
        //TODO: Вывести дерево
        for (const auto &element : set) {
            std::cout << element.width << ' ' << element.height << std::endl;
        }
    } else {
        std::cout << "Chaos" << std::endl;
    }

    return 0;
}