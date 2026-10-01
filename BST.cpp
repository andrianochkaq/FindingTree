#include "BST.h"
#include <iostream>

BST::Node::Node(int value)
{
    key = value;
    left = nullptr;
    right = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clear();
}


// =============================
// INSERT
// =============================

BST::Node* BST::insert(Node* node, int key, int& visited)
{
    if (node == nullptr)
    {
        return new Node(key);
    }

    visited++;

    if (key < node->key)
    {
        node->left = insert(node->left, key, visited);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, visited);
    }

    return node;
}

void BST::insert(int key, int& visited)
{
    visited = 0;
    root = insert(root, key, visited);
}


// =============================
// SEARCH
// =============================

bool BST::search(Node* node, int key, int& visited)
{
    if (node == nullptr)
    {
        return false;
    }

    visited++;

    if (key == node->key)
    {
        return true;
    }

    if (key < node->key)
    {
        return search(node->left, key, visited);
    }

    return search(node->right, key, visited);
}

bool BST::search(int key, int& visited)
{
    visited = 0;

    return search(root, key, visited);
}


// =============================
// DELETE
// =============================

BST::Node* BST::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

BST::Node* BST::remove(Node* node, int key, bool& removed)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (key < node->key)
    {
        node->left = remove(node->left, key, removed);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key, removed);
    }
    else
    {
        removed = true;

        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMin(node->right);

        node->key = temp->key;

        bool tempRemoved = false;

        node->right = remove(
            node->right,
            temp->key,
            tempRemoved
        );
    }

    return node;
}

bool BST::remove(int key)
{
    bool removed = false;

    root = remove(root, key, removed);

    return removed;
}


// =============================
// PRINT DESCENDING
// =============================

void BST::printDescending(Node* node, int& visited)
{
    if (node == nullptr)
    {
        return;
    }

    visited++;

    printDescending(node->right, visited);

    std::cout << node->key << " ";

    printDescending(node->left, visited);
}

void BST::printDescending(int& visited)
{
    visited = 0;

    printDescending(root, visited);

    std::cout << std::endl;
}


// =============================
// PRINT TREE
// =============================

void BST::printTree(Node* node, int level)
{
    if (node == nullptr)
    {
        return;
    }

    printTree(node->right, level + 1);

    for (int i = 0; i < level; i++)
    {
        std::cout << "    ";
    }

    std::cout << node->key << std::endl;

    printTree(node->left, level + 1);
}

void BST::print()
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

int BST::getHeight(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}

int BST::height()
{
    return getHeight(root);
}


// =============================
// SIZE
// =============================

int BST::getSize(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 +
        getSize(node->left) +
        getSize(node->right);
}

int BST::size()
{
    return getSize(root);
}


// =============================
// CLEAR
// =============================

void BST::clear(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
}

void BST::clear()
{
    clear(root);

    root = nullptr;
}


// =============================
// COPY
// =============================

void BST::copyTree(Node* node, BST& tree)
{
    if (node == nullptr)
    {
        return;
    }

    int visited = 0;

    tree.insert(node->key, visited);

    copyTree(node->left, tree);
    copyTree(node->right, tree);
}

void BST::copyTo(BST& tree)
{
    tree.clear();

    copyTree(root, tree);
}
