// Iterator Pattern
// Provides a way to sequentially access elements of a collection without
// exposing the underlying representation.

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// A simple binary tree with an in-order iterator
struct TreeNode {
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int v) : value(v) {}
};

// In-order iterator using an explicit stack
class InOrderIterator {
    std::vector<TreeNode*> stack;

    void pushLeft(TreeNode* node) {
        while (node) { stack.push_back(node); node = node->left; }
    }

public:
    explicit InOrderIterator(TreeNode* root) { pushLeft(root); }

    bool hasNext() const { return !stack.empty(); }

    int next() {
        if (!hasNext()) throw std::out_of_range("no more elements");
        TreeNode* node = stack.back();
        stack.pop_back();
        pushLeft(node->right);
        return node->value;
    }
};

int main() {
    // Tree layout:
    //   4 -> left: 2, right: 6
    //   2 -> left: 1, right: 3
    //   6 -> left: 5, right: 7
    TreeNode nodes[] = {
        TreeNode(4), TreeNode(2), TreeNode(6),
        TreeNode(1), TreeNode(3), TreeNode(5), TreeNode(7)
    };
    nodes[0].left  = &nodes[1]; nodes[0].right = &nodes[2];
    nodes[1].left  = &nodes[3]; nodes[1].right = &nodes[4];
    nodes[2].left  = &nodes[5]; nodes[2].right = &nodes[6];

    InOrderIterator it(&nodes[0]);
    std::cout << "In-order traversal: ";
    while (it.hasNext()) std::cout << it.next() << " ";
    std::cout << "\n";
}
