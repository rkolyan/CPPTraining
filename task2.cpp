//
// Created by rkolyan on 06.04.2024.
//

#include <iostream>
#include <set>

struct Node {
    int x;
    int y;
    int diff;
    bool operator<(const Node &element) const {
        return diff < element.diff;
    }
    Node(int x, int y, int diff) {
        this->x = x;
        this->y = y;
        this->diff = diff;
    }
};

class Diffs {
private:
    std::set<Node> nodes;
    int b, c, r, d;
public:


    Diffs(int b, int c, int r, int d) {
        this->b = b;
        this->c = c;
        this->r = r;
        this->d = d;
        for (int x = 1, y = 1; x <= b; ) {
            if (x * 1000000 - y * r < 0) {
                x++;
            } else {
                if (x * 1000000 - (y + 1) * r > 0) {
                    y++;
                } else {
                    nodes.emplace(x, y, x*1000000-y*r);
                }
            }
        }
    }
};

int main(void) {
    int b = 0, c = 0, r = 0, d = 0;
    std::cin >> b >> c;
    std::cin >> r >> d;
    return 0;
}