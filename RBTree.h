#pragma once
#include "Tree234.h"

class RBTree
{
private:
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        int key;
        Color color;

        Node* left;
        Node* right;
        Node* parent;

        Node(int value);
    };

    Node* root;

    void leftRotate(Node* node);
    void rightRotate(Node* node);

    void insertFix(Node* node);

    Node* insert(Node* node, int key, int& visited);

    bool search(Node* node, int key, int& visited);

    Node* minimum(Node* node);

    void transplant(Node* first, Node* second);

    void deleteFix(Node* node, Node* parent);

    void deleteNode(Node* node);

    void printDescending(Node* node, int& visited);
    void printTree(Node* node, int level);

    void clear(Node* node);

    int getHeight(Node* node);
    int getSize(Node* node);

    void copyTree(Node* node, RBTree& tree);
    Tree234::Node* convertNode(Node* black, int& visited);

public:
    RBTree();
    ~RBTree();
    void toTwoThreeFour(Tree234& tree, int& visited);
    void insert(int key, int& visited);

    bool search(int key, int& visited);

    bool remove(int key);

    void printDescending(int& visited);
    void print();

    int height();
    int size();

    void clear();

    void copyTo(RBTree& tree);
};