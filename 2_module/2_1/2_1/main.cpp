#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>


template <class T, class Compare = std::less<int>>
class BinaryTree {
    struct Node;
public:
    BinaryTree() : Root(nullptr) {}
    BinaryTree(Compare comp) : Root(nullptr), Comp(comp) {}
    ~BinaryTree() {
        destroy();
    };

    void Insert(const T& key) {
        auto node = new Node(key, nullptr, nullptr);

        if (Root == nullptr) {
            Root = node;
            return;
        }

        else {
            auto curr = Root;
            while (curr->Left != nullptr || curr->Right != nullptr) {
                if (curr->Key > key) {
                    if (curr->Left == nullptr)
                        break;
                    curr = curr->Left;
                }
                else {
                    if (curr->Right == nullptr)
                        break;
                    curr = curr->Right;
                }
            }
            if (Comp(key, curr->Key))
                curr->Left = node;
            else
                curr->Right = node;
        }
    }

    bool Erase(const T& key) {
        if (Root == nullptr)
            return false;
        else {
            auto curr = Root;
            Node* parent = nullptr;
            while ((Comp(curr->Key, key) || Comp(key, curr->Key)) && curr != nullptr) {
                parent = curr;
                if (Comp(curr->Key, key))
                    curr = curr->Right;
                else
                    curr = curr->Left;
            }
            if (curr == nullptr)
                return false;
            if (curr != Root)
                deleteNode((Comp(curr->Key, key)) ? (parent->Right) : (parent->Left));
            else
                deleteNode(Root);
            return true;
        }
    }

    Node Find(const T& key) {
        assert(Root != nullptr);
        auto node = Root;
        while (node != nullptr && (Comp(node->Key, key) || Comp(key, node->Key))) {
            node = Comp(node->Key, key) ? (node->Right) : (node->Left);
        }
        return *node;
    }

    T FindMin() {
        assert(Root != nullptr);
        auto node = Root;
        while (node->Left != nullptr)
            node = node->Left;
        return node->Key;
    }

    T FindMax() {
        assert(Root != nullptr);
        auto node = Root;
        while (node->Right != nullptr)
            node = node->Right;
        return node->Key;
    }

    void InorderPrint() {
        inorderPrint(Root);
    }

    size_t Height() {
        std::vector<Node*> level;
        std::vector<Node*> temp;
        level.push_back(Root);
        size_t maxDepth = 0;
        while (level.size() != 0) {
            for (size_t i = 0; i < level.size(); ++i) {
                if (level[i]->Left != nullptr) {
                    temp.push_back(level[i]->Left);
                }
                if (level[i]->Right != nullptr) {
                    temp.push_back(level[i]->Right);
                }
            }
            level = temp;
            temp.clear();
            if (level.size() != 0) {
                ++maxDepth;
            }
        }
        return maxDepth;
    }
private:
    struct Node {
        T Key;
        Node* Left = nullptr;
        Node* Right = nullptr;
        Node(const T& key, Node* left, Node* right)
            : Key(key), Left(left), Right(right)
        {}
    };
    Node* Root;
    Compare Comp;

    void inorderPrint(Node* node) {
        if (node == nullptr)
            return;
        inorderPrint(node->Left);
        std::cout << node->Key << ' ';
        inorderPrint(node->Right);
    }
    void destroy() {
        if (Root == nullptr)
            return;
        std::queue<Node*> q;
        q.push(Root);
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            if (node->Left != nullptr)
                q.push(node->Left);
            if (node->Right != nullptr)
                q.push(node->Right);
            delete node;
        }
        Root = nullptr;
    }
    void deleteNode(Node*& node) {
        if (node->Right == nullptr) {
            Node* tmp = node->Left;
            delete node;
            node = tmp;
        }
        else if (node->Left == nullptr) {
            Node* tmp = node->Right;
            delete node;
            node = tmp;
        }
        else {
            Node* minParent = node;
            Node* min = node->Right;
            while (min->Left != nullptr) {
                minParent = min;
                min = min->Left;
            }
            if (min == node->Right)
                minParent->Right = min->Right;
            else
                minParent->Left = min->Right;
            min->Left = node->Left;
            min->Right = node->Right;
            delete node;
            node = min;
        }
    }
};


int main()
{
    int n = 0;
    std::cin >> n;
    assert(n > 0);
    BinaryTree<int> tree;
    for (int i = 0, k = 0; i < n; i++) {
        std::cin >> k;
        tree.Insert(k);
    }
    tree.InorderPrint();
 
    system("pause");
    return 0;
}
