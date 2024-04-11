#pragma once
#include <iomanip>

class BinTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(const int k) : data(k), left(nullptr), right(nullptr) {}
    };

    Node* _root;
    Node* copyTree(const Node* otherNode);
    Node* findMin(Node* node) const;
    Node* search_rec(Node* node, int key);
    void delete_rec(Node*& node, const int key);
    void destroy_rec(Node* node);
    void print_rec(Node* node, const std::string& prefix = "", bool isLeft = true) const;
    bool contains_rec(Node* node, const int key) const;
    int count_rec(Node* node);

public:
    BinTree();
    BinTree(const BinTree& other);
    ~BinTree();
    BinTree& operator=(const BinTree& other);

    void print() const;
    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
    int count();
    bool search(int key);
};
