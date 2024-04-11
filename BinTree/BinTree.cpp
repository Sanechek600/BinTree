#include <iostream>

#include "BinTree.h"

BinTree::BinTree() : _root(nullptr) {}
BinTree::Node* BinTree::copyTree(const Node* otherNode) {
    if (!otherNode) {
        return nullptr;
    }
    Node* newNode = new Node(otherNode->data);
    newNode->left = copyTree(otherNode->left);
    newNode->right = copyTree(otherNode->right);
    return newNode;
}
BinTree::BinTree(const BinTree& other) : _root(copyTree(other._root)) {}
void BinTree::destroy_rec(Node* node) {
    if (node) {
        destroy_rec(node->left);
        destroy_rec(node->right);
        delete node;
    }
}
BinTree::~BinTree() {
    destroy_rec(_root);
}
BinTree& BinTree::operator=(const BinTree& other) {
    BinTree copy(other);
    if (this != &copy) {
        std::swap(*this, copy);
    }
    return *this;
}
void BinTree::print_rec(Node* root, const std::string& prefix, bool isLeft) const {
    if (root) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "\n--");

        std::cout << root->data << std::endl;

        print_rec(root->left, prefix + (isLeft ? "|   " : "    "), true);
        print_rec(root->right, prefix + (isLeft ? "|   " : "    "), false);
    }
}
void BinTree::print() const {
    std::cout << "Tree: " << std::endl;
    print_rec(_root);
}
bool BinTree::insert(int key) {
    if (!_root) {
        _root = new Node(key);
        return true;
    }

    Node* tmp = _root;
    while (tmp && (tmp->data != key)) {
        if (tmp->data > key) {
            if (tmp->left)
                tmp = tmp->left;
            else {
                tmp->left = new Node(key);
                return true;
            }
        }
        else if (tmp->data < key) {
            if (tmp->right)
                tmp = tmp->right;
            else {
                tmp->right = new Node(key);
                return true;
            }
        }
        else
            return false;
    }
    return false;
}
bool BinTree::contains_rec(Node* node, const int key) const {
    if (node) {
        if (node->data == key) return true;
        else if (node->data < key) return contains_rec(node->right, key);
        else return contains_rec(node->left, key);
    }
    else
        return false;
}
bool BinTree::contains(int key) const {
    return contains_rec(_root, key);
}
void BinTree::delete_rec(Node*& node, const int key) {
    if (!node) {
        return;
    }
    if (key < node->data) {
        delete_rec(node->left, key);
    }
    else if (key > node->data) {
        delete_rec(node->right, key);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else {
            node->data = findMin(node->right)->data;
            delete_rec(node->right, node->data);
        }
    }
}
BinTree::Node* BinTree::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
bool BinTree::erase(int key) {
    if (contains(key)) {
        delete_rec(_root, key);
        return true;
    }
    return false;
}
int BinTree::count_rec(Node* node) {
    if (!node)
        return 0;
    return count_rec(node->right) + count_rec(node->left) + 1;
}
int BinTree::count() {
    return count_rec(_root);
}
BinTree::Node* BinTree::search_rec(Node* node, int key) {
    if (node == nullptr || node->data == key)
        return _root;

    if (node->data < key)
        return search_rec(node->right, key);

    return search_rec(node->left, key);
}
bool BinTree::search(int key) {
    if (search_rec(_root, key)) return true;
    return false;
}