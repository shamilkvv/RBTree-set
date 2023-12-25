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

    Node* parent(Node* root, Node* n) {
        if (root == nullptr || root == n) {
            return nullptr;
        }

        if (root->left == n || root->right == n) {
            return root;
        }

        Node* leftParent = parent(root->left, n);
        if (leftParent != nullptr) {
            return leftParent;
        }

        return parent(root->right, n);
    }

    Node* parent(Node* n) {
        if (n != nullptr && n != root) {
            return parent(root, n);
        }
        else {
            return nullptr;
        }
    }

    Node* sibling(Node* n) {
        Node* p = parent(n);
        if (n == p->left) {
            return p->right;
        }
        else {
            return p->left;
        }
    }

    void deleteCase1(Node* n) {
        if (n != root) {
            deleteCase2(n);
        }
    }

    void deleteCase2(Node* n) {
        Node* s = sibling(n);
        Node* p = parent(n);
        if (s->isRed) {
            p->isRed = true;
            s->isRed = false;
            if (n == p->left) {
                rotateLeft(p);
            }
            else {
                rotateRight(p);
            }
        }
        deleteCase3(n);
    }

    void deleteCase3(Node* n) {
        Node* s = sibling(n);
        Node* p = parent(n);
        if (!p->isRed && !s->isRed && !s->left->isRed && !s->right->isRed) {
            s->isRed = true;
            deleteCase1(p);
        }
        else {
            deleteCase4(n);
        }
    }

    void deleteCase4(Node* n) {
        Node* s = sibling(n);
        Node* p = parent(n);
        if (p->isRed && !s->isRed && !s->left->isRed && !s->right->isRed) {
            p->isRed = true;
            s->isRed = false;
        }
        else {
            deleteCase5(n);
        }
    }

    void deleteCase5(Node* n) {
        Node* s = sibling(n);
        Node* p = parent(n);
        if (!s->isRed) {
            if (n == p->left && !s->right->isRed && s->left->isRed) {
                s->isRed = true;
                s->left->isRed = false;
                rotateRight(s);
            }
            else if (n == p->right && !s->left->isRed && s->right->isRed) {
                s->isRed = true;
                s->right->isRed = false;
                rotateLeft(s);
            }
        }
        deleteCase6(n);
    }

    void deleteCase6(Node* n) {
        Node* s = sibling(n);
        Node* p = parent(n);
        s->isRed = p->isRed;
        p->isRed = false;
        if (n == p->left) {
            s->right->isRed = false;
            rotateLeft(p);
        }
        else {
            s->left->isRed = false;
            rotateRight(p);
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