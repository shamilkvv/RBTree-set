#include <iostream>
#include <vector>
#include <algorithm>

class RBTree {
public:
    class Node {
    public:
        bool isRed;
        int val;
        Node* parent;
        Node* left;
        Node* right;

        Node() : val(0), isRed(true), left(nullptr), right(nullptr) {}
        Node(int x) : val(x), isRed(true), left(nullptr), right(nullptr) {}
    };

    Node* root;
    std::vector <Node*> arr;

    RBTree() : root(nullptr) {}
    RBTree(int v) : root(new Node(v)) {}
    ~RBTree() {
        if (root != nullptr) {
            destruct(root);
            delete root;
        }
        arr.clear();
    }

    void destruct(Node* node) {
        if (node != nullptr) {
            destruct(node->left);
            destruct(node->right);
            delete node;
        }
    }

    bool isRed(Node* node) {
        return (node != nullptr) ? node->isRed : false;
    }

    void rotateRight(Node*& node) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;

        temp->isRed = node->isRed;
        node->isRed = true;
        node = temp;
    }

    void rotateLeft(Node*& node) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        temp->isRed = node->isRed;
        node->isRed = true;
        node = temp;
    }

    void flipColor(Node*& node) {
        node->isRed = true;
        if (node->left != nullptr) node->left->isRed = false;
        if (node->right != nullptr) node->right->isRed = false;
    }

    void buildTree() {
        int tempArr[10] = { 3,4,7,1,2,9,8,6,5,10 };
        for (int i = 0; i != 10; i++) {
            arr.push_back(new Node(tempArr[i]));
            insert(root, arr[i]);
        }
        display(root);
    }

    void insert(Node*& node, Node*& vNode) {
        if (node == nullptr) {
            node = vNode;
        }
        else if (node->val > vNode->val) {
            insert(node->left, vNode);
        }
        else if (node->val < vNode->val) {
            insert(node->right, vNode);
        }

        if (isRed(node->right) && !isRed(node->left)) {
            rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)) {
            flipColor(node);
        }
    }
    void display(Node* node) {
        if (node == NULL) {
            return;
        }
        display(node->left);

        std::cout << node->val << "  ";
        display(node->right);
    }
};

class Set : public RBTree {
public:
    Set() {}

    Set(std::initializer_list<int> values) {
        for (int value : values) {
            Node* newNode = new Node(value);
            insert(root, newNode);
            arr.push_back(newNode);
        }
    }

    void insertSet(int x) {
        Node* newNode = new Node(x);
        insert(root, newNode);
        arr.push_back(newNode);
    }

    bool contains(int x) {
        for (const auto& el : arr) {
            if (el->val == x) {
                return true;
            }
        }
        insertSet(x);
        return false;
    }

    void displaySet() {
        if (root == nullptr) {
            std::cout << "set is empty" << "\n";
            return;
        }
        display(root);
        std::cout << "\n";
    }
};

int main() {

   

    return 0;
}