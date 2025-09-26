#include <list>

struct Node {
	Node(unsigned int width, unsigned int height): width{width}, height{height} {
		min_height = height;
	}
	bool operator<(const Node &other) const {
		return width < other.width;
	}
	bool height_less_eq(const Node &other) const {
		return height <= other.height || min_height <= other.height;
	}
	void update_min_height(unsigned int new_min_height) const {
		min_height = new_min_height;
	}
	unsigned int width, height;
	mutable unsigned int min_height;
};

bool is_fully_intersected(const std::list<Node> &list);
bool is_fully_intersected_right(const std::list<Node> &list);