#pragma once

class Tree234
{
public:
    struct Node
    {
        int keys[3];
        Node* children[4];
        int count;          // кількість ключів (1..3)

        Node();
    };

    Tree234();
    ~Tree234();

    void print();
    int height();
    int size();             // кількість вузлів 2-3-4
    int keysCount();        // кількість ключів
    void clear();

    Node* root;

private:
    void printTree(Node* node, int level);
    int getHeight(Node* node);
    int getSize(Node* node);
    int getKeysCount(Node* node);
    void clear(Node* node);
};