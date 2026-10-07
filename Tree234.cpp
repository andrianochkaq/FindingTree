#include "Tree234.h"
#include <iostream>

Tree234::Node::Node()
{
    count = 0;

    for (int i = 0; i < 3; i++)
    {
        keys[i] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        children[i] = nullptr;
    }
}

Tree234::Tree234()
{
    root = nullptr;
}

Tree234::~Tree234()
{
    clear();
}


// =============================
// PRINT TREE
// =============================

void Tree234::printTree(Node* node, int level)
{
    if (node == nullptr)
    {
        return;
    }

    // верхня половина дітей (праворуч)
    int mid = (node->count + 1) / 2;

    for (int i = node->count; i >= mid; i--)
    {
        printTree(node->children[i], level + 1);
    }

    for (int i = 0; i < level; i++)
    {
        std::cout << "    ";
    }

    std::cout << "[";

    for (int i = 0; i < node->count; i++)
    {
        if (i > 0)
        {
            std::cout << " ";
        }

        std::cout << node->keys[i];
    }

    std::cout << "]" << std::endl;

    // нижня половина дітей (ліворуч)
    for (int i = mid - 1; i >= 0; i--)
    {
        printTree(node->children[i], level + 1);
    }
}

void Tree234::print()
{
    if (root == nullptr)
    {
        std::cout << "(порожнє дерево)" << std::endl;
        return;
    }

    printTree(root, 0);
}


// =============================
// HEIGHT
// =============================

int Tree234::getHeight(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int maxHeight = 0;

    for (int i = 0; i <= node->count; i++)
    {
        int h = getHeight(node->children[i]);

        if (h > maxHeight)
        {
            maxHeight = h;
        }
    }

    return maxHeight + 1;
}

int Tree234::height()
{
    return getHeight(root);
}


// =============================
// SIZE
// =============================

int Tree234::getSize(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int total = 1;

    for (int i = 0; i <= node->count; i++)
    {
        total += getSize(node->children[i]);
    }

    return total;
}

int Tree234::size()
{
    return getSize(root);
}

int Tree234::getKeysCount(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int total = node->count;

    for (int i = 0; i <= node->count; i++)
    {
        total += getKeysCount(node->children[i]);
    }

    return total;
}

int Tree234::keysCount()
{
    return getKeysCount(root);
}


// =============================
// CLEAR
// =============================

void Tree234::clear(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    for (int i = 0; i <= node->count; i++)
    {
        clear(node->children[i]);
    }

    delete node;
}

void Tree234::clear()
{
    clear(root);

    root = nullptr;
}