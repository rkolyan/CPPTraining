//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <vector>

struct Node {
    unsigned int width;
    unsigned int height;
};

int main() {
    unsigned int N = 0;
    std::cin >> N;

    std::vector<Node> nodes;
    nodes.resize(N);

    for (unsigned int i = 0; i < N; i++) {
        std::cin >> nodes[i].width >> nodes[i].height;
    }
    bool chaos = false;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = i + 1; j < N; j++) {
            if (nodes[i].width <= nodes[j].width && nodes[i].height <= nodes[j].height) {
                chaos = true;
                goto bzhe;
            }
        }
    }

    bzhe:
    if (!chaos) {
        std::cout << "Well done";
    } else {
        std::cout << "Invisible paper detected";
    }
    return 0;
}