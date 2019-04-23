#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>

template <class T, class Compare = std::less<int>>
class AVLTree {
    struct AVL_Node;
public:
    AVLTree() = default;

    size_t Insert(const T& value) {
        size_t position = 0;
        insert(Root, value, position);
        return position;
    }
    
    void Erase(size_t pos) {
        erase(Root, pos);

    }

    ~AVLTree() {
        destroy(Root);
    }
private:
    AVL_Node* Root = nullptr;
    Compare Comp;

    void destroy(AVL_Node* node) {
        if (node == nullptr)
            return;
        destroy(node->Left);
        destroy(node->Right);
        delete node;
    }
    size_t count_children(AVL_Node*& root) {
        if (root == nullptr) {
            return 0;
        }
        else {
            return root->children;
        }
    }

    size_t count_height(AVL_Node*& root) {
        if (root == nullptr) {
            return 0;
        }
        else {
            return root->height;
        }
    }

    void rotate_Left(AVL_Node*& root) {
        AVL_Node* tmp = root;
        root = root->Right;
        tmp->Right = root->Left;
        root->Left = tmp;
        root->Left->height = std::max(count_height(root->Left->Left), count_height(root->Left->Right)) + 1;
        root->height = std::max(count_height(root->Left), count_height(root->Right)) + 1;
        root->Left->children = count_children(root->Left->Left) + count_children(root->Left->Right) + 1;
        root->children = count_children(root->Right) + count_children(root->Left) + 1;
    }

    void rotate_Right(AVL_Node*& root) {
        AVL_Node* tmp = root;
        root = root->Left;
        tmp->Left = root->Right;
        root->Right = tmp;
        root->Right->height = std::max(count_height(root->Right->Left), count_height(root->Right->Right)) + 1;
        root->height = std::max(count_height(root->Left), count_height(root->Right)) + 1;
        root->Right->children = count_children(root->Right->Left) + count_children(root->Right->Right) + 1;
        root->children = count_children(root->Right) + count_children(root->Left) + 1;
    }

    void big_rotate_Left(AVL_Node*& root) {
        rotate_Left(root);
        rotate_Left(root->Left);
        rotate_Right(root);
    }

    void big_rotate_Right(AVL_Node*& root) {
        rotate_Right(root);
        rotate_Right(root->Right);
        rotate_Left(root);
    }

    void balance(AVL_Node*& root) {
        if (root != nullptr) {
            root->height = std::max(count_height(root->Right), count_height(root->Left)) + 1;
            if (count_height(root->Left) - count_height(root->Right) == -2) {
                if (count_height(root->Right->Left) <= count_height(root->Right->Right)) {
                    rotate_Left(root);
                }
                else {
                    big_rotate_Left(root);
                }
            }
            else if (count_height(root->Left) - count_height(root->Right) == 2) {
                if (count_height(root->Left->Right) <= count_height(root->Left->Left)) {
                    rotate_Right(root);
                }
                else {
                    big_rotate_Right(root);
                }
            }
        }
    }

    void insert(AVL_Node*& root, const T& value, size_t& result) {
        if (root == nullptr) {
            root = new AVL_Node(value);
        }
        else {
            ++(root->children);
            if (Comp(value, root->Data)) {
                result += count_children(root->Right) + 1;
                insert(root->Left, value, result);
            }
            else {
                insert(root->Right, value, result);
            }
            balance(root);
        }
    }

    void erase(AVL_Node*& root, size_t pos) {
        if (root != nullptr) {
            size_t r_elem = count_children(root->Right);
            if (r_elem < pos) {
                --root->children;
                pos -= (r_elem + 1);
                erase(root->Left, pos);
            }
            else if (r_elem > pos) {
                --root->children;
                erase(root->Right, pos);
            }
            else {
                if (root->Left == nullptr) {
                    if (root->Right == nullptr) {
                        root = nullptr;
                    }
                    else {
                        root = root->Right;
                    }
                }
                else if (root->Right == nullptr) {
                    root = root->Left;
                }
                else {
                    T value = root->Data;
                    AVL_Node* node_right = root->Right;
                    while (node_right->Left != nullptr) {
                        node_right = node_right->Left;
                    }
                    AVL_Node* node_left = root->Left;
                    while (node_left->Right != nullptr) {
                        node_left = node_left->Right;
                    }
                    if (Comp(value - node_left->Data, node_right->Data - value)) {
                        erase(root, pos + 1);
                        node_left->Left = root->Left;
                        node_left->Right = root->Right;
                        node_left->children = root->children;
                        root = node_left;
                    }
                    else {
                        erase(root, pos - 1);
                        node_right->Left = root->Left;
                        node_right->Right = root->Right;
                        node_right->children = root->children;
                        root = node_right;
                    }
                }
                balance(root);
            }
        }
    }

    struct AVL_Node {
        T Data;
        size_t height;
        size_t children;
        AVL_Node* Left;
        AVL_Node* Right;
        AVL_Node(const T& d) : 
            Data(d), height(1), children(1), Left(nullptr), Right(nullptr) {}
    };
};


int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    int command = 0;
    int value = 0;
    AVLTree<int> tree;
    for (int i = 0; i < n; ++i) {
        std::cin >> command >> value;
        switch (command)
        {
            case 1: 
            {
                std::cout << tree.Insert(value) << std::endl;
                break;
            }
            case 2:
            {
                tree.Erase(value);
                break;
            }
        default:
            break;
        }
    }
    return 0;
}