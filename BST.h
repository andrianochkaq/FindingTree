#pragma once

class BST
{
private:
    struct Node
    {
        int key;
        Node* left;
        Node* right;

        Node(int value);
    };

    Node* root;

    Node* insert(Node* node, int key, int& visited);
    bool search(Node* node, int key, int& visited);

    Node* remove(Node* node, int key, bool& removed);
    Node* findMin(Node* node);

    void printDescending(Node* node, int& visited);
    void printTree(Node* node, int level);

    void clear(Node* node);

    int getHeight(Node* node);
    int getSize(Node* node);

    void copyTree(Node* node, BST& tree);

public:
    BST();
    ~BST();

    void insert(int key, int& visited);

    bool search(int key, int& visited);

    bool remove(int key);

    void printDescending(int& visited);
    void print();

    int height();
    int size();

    void clear();

    void copyTo(BST& tree);
};
