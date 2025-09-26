#include <iostream>
#include <set>

struct Node {
    Node(unsigned int width, unsigned int height) : _width{width}, _height{height} {

    }
	bool operator<(const Node &other) const {
		return _width < other._width;
	}
	unsigned int _width, _min_width, _height;
};

int main() {
	unsigned int width = 4, height = 4;
	std::set<Node> nodes;
    auto iter = nodes.emplace(width, height).first;
    int flag1 = static_cast<int>(iter == nodes.cbegin());
    std::cout << flag1 << std::endl;
    iter--;
    flag1 = static_cast<int>(iter == nodes.cend());
    std::cout << flag1 << std::endl;
    flag1 = static_cast<int>(iter == nodes.cbegin());
    std::cout << flag1 << std::endl;
    iter = std::prev(iter);
    flag1 = static_cast<int>(iter == nodes.cend());
    std::cout << flag1 << std::endl;
    flag1 = static_cast<int>(iter == nodes.cbegin());
    std::cout << flag1 << std::endl;
    return 0;
}