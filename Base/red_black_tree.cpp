//
// Created by rkolyan on 29.06.2024.
//


#include <cstddef>
#include <stack>

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        size_t size;
        bool red;
        bool leaf;
        struct Node *left;
        struct Node *right;
    };
    //TODO: Нужно уметь балансировать деревья
    struct Node *tree;
public:
    RedBlackTree() {
        tree = nullptr;
    }
    ~RedBlackTree() {
        std::stack<Node *> next_nodes;
        Node *current = nullptr;
        next_nodes.push(tree);
        while (!next_nodes.empty()) {
            current = next_nodes.top();
            next_nodes.pop();
            for (const auto &node : {current->left, current->right}) {
                if (node) {
                    next_nodes.push(node);
                }
            }
            delete current;
        }
    }
    void addElement(T element);
    void deleteElement(size_t index);
    T getElement(size_t index);
};