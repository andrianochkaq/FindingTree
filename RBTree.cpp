#include "RBTree.h"
#include <iostream>

RBTree::Node::Node(int value)
{
    key = value;
    color = RED;

    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

RBTree::RBTree()
{
    root = nullptr;
}

RBTree::~RBTree()
{
    clear();
}


// ======================================
// LEFT ROTATE
// ======================================

void RBTree::leftRotate(Node* node)
{
    Node* rightNode = node->right;

    node->right = rightNode->left;

    if (rightNode->left != nullptr)
    {
        rightNode->left->parent = node;
    }

    rightNode->parent = node->parent;

    if (node->parent == nullptr)
    {
        root = rightNode;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = rightNode;
    }
    else
    {
        node->parent->right = rightNode;
    }

    rightNode->left = node;
    node->parent = rightNode;
}


// ======================================
// RIGHT ROTATE
// ======================================

void RBTree::rightRotate(Node* node)
{
    Node* leftNode = node->left;

    node->left = leftNode->right;

    if (leftNode->right != nullptr)
    {
        leftNode->right->parent = node;
    }

    leftNode->parent = node->parent;

    if (node->parent == nullptr)
    {
        root = leftNode;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = leftNode;
    }
    else
    {
        node->parent->left = leftNode;
    }

    leftNode->right = node;
    node->parent = leftNode;
}


// ======================================
// INSERT
// ======================================

void RBTree::insert(int key, int& visited)
{
    visited = 0;

    Node* newNode = new Node(key);

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr)
    {
        visited++;

        parent = current;

        if (key < current->key)
        {
            current = current->left;
        }
        else if (key > current->key)
        {
            current = current->right;
        }
        else
        {
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;

    if (parent == nullptr)
    {
        root = newNode;
    }
    else if (key < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    insertFix(newNode);
}

void RBTree::insertFix(Node* node)
{
    while (
        node != root &&
        node->parent != nullptr &&
        node->parent->color == RED)
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    node = parent;

                    leftRotate(node);

                    parent = node->parent;
                    grandparent = parent->parent;
                }

                parent->color = BLACK;
                grandparent->color = RED;

                rightRotate(grandparent);
            }
        }
        else
        {
            Node* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    node = parent;

                    rightRotate(node);

                    parent = node->parent;
                    grandparent = parent->parent;
                }

                parent->color = BLACK;
                grandparent->color = RED;

                leftRotate(grandparent);
            }
        }
    }

    root->color = BLACK;
}


// ======================================
// SEARCH
// ======================================

bool RBTree::search(Node* node, int key, int& visited)
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

bool RBTree::search(int key, int& visited)
{
    visited = 0;

    return search(root, key, visited);
}


// ======================================
// MINIMUM
// ======================================

RBTree::Node* RBTree::minimum(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}


// ======================================
// TRANSPLANT
// ======================================

void RBTree::transplant(Node* first, Node* second)
{
    if (first->parent == nullptr)
    {
        root = second;
    }
    else if (first == first->parent->left)
    {
        first->parent->left = second;
    }
    else
    {
        first->parent->right = second;
    }

    if (second != nullptr)
    {
        second->parent = first->parent;
    }
}


// ======================================
// DELETE
// ======================================

bool RBTree::remove(int key)
{
    Node* node = root;

    while (node != nullptr)
    {
        if (key == node->key)
        {
            deleteNode(node);
            return true;
        }

        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    return false;
}

void RBTree::deleteNode(Node* node)
{
    Node* replacement = node;
    Node* child = nullptr;
    Node* parent = nullptr;

    Color originalColor = replacement->color;

    if (node->left == nullptr)
    {
        child = node->right;
        parent = node->parent;

        transplant(node, node->right);
    }
    else if (node->right == nullptr)
    {
        child = node->left;
        parent = node->parent;

        transplant(node, node->left);
    }
    else
    {
        replacement = minimum(node->right);

        originalColor = replacement->color;
        child = replacement->right;

        if (replacement->parent == node)
        {
            parent = replacement;

            if (child != nullptr)
            {
                child->parent = replacement;
            }
        }
        else
        {
            parent = replacement->parent;

            transplant(
                replacement,
                replacement->right
            );

            replacement->right = node->right;
            replacement->right->parent = replacement;
        }

        transplant(node, replacement);

        replacement->left = node->left;
        replacement->left->parent = replacement;

        replacement->color = node->color;
    }

    delete node;

    if (originalColor == BLACK)
    {
        deleteFix(child, parent);
    }
}


// ======================================
// DELETE FIX
// ======================================

void RBTree::deleteFix(Node* node, Node* parent)
{
    while (
        node != root &&
        (node == nullptr || node->color == BLACK))
    {
        if (parent == nullptr)
        {
            break;
        }

        if (node == parent->left)
        {
            Node* brother = parent->right;

            if (brother != nullptr &&
                brother->color == RED)
            {
                brother->color = BLACK;
                parent->color = RED;

                leftRotate(parent);

                brother = parent->right;
            }

            if (brother == nullptr)
            {
                node = parent;
                parent = node->parent;
            }
            else
            {
                bool leftBlack =
                    brother->left == nullptr ||
                    brother->left->color == BLACK;

                bool rightBlack =
                    brother->right == nullptr ||
                    brother->right->color == BLACK;

                if (leftBlack && rightBlack)
                {
                    brother->color = RED;

                    node = parent;
                    parent = node->parent;
                }
                else
                {
                    if (rightBlack)
                    {
                        if (brother->left != nullptr)
                        {
                            brother->left->color = BLACK;
                        }

                        brother->color = RED;

                        rightRotate(brother);

                        brother = parent->right;
                    }

                    brother->color = parent->color;
                    parent->color = BLACK;

                    if (brother->right != nullptr)
                    {
                        brother->right->color = BLACK;
                    }

                    leftRotate(parent);

                    node = root;
                    parent = nullptr;
                }
            }
        }
        else
        {
            Node* brother = parent->left;

            if (brother != nullptr &&
                brother->color == RED)
            {
                brother->color = BLACK;
                parent->color = RED;

                rightRotate(parent);

                brother = parent->left;
            }

            if (brother == nullptr)
            {
                node = parent;
                parent = node->parent;
            }
            else
            {
                bool leftBlack =
                    brother->left == nullptr ||
                    brother->left->color == BLACK;

                bool rightBlack =
                    brother->right == nullptr ||
                    brother->right->color == BLACK;

                if (leftBlack && rightBlack)
                {
                    brother->color = RED;

                    node = parent;
                    parent = node->parent;
                }
                else
                {
                    if (leftBlack)
                    {
                        if (brother->right != nullptr)
                        {
                            brother->right->color = BLACK;
                        }

                        brother->color = RED;

                        leftRotate(brother);

                        brother = parent->left;
                    }

                    brother->color = parent->color;
                    parent->color = BLACK;

                    if (brother->left != nullptr)
                    {
                        brother->left->color = BLACK;
                    }

                    rightRotate(parent);

                    node = root;
                    parent = nullptr;
                }
            }
        }
    }

    if (node != nullptr)
    {
        node->color = BLACK;
    }
}


// ======================================
// PRINT DESCENDING
// ======================================

void RBTree::printDescending(Node* node, int& visited)
{
    if (node == nullptr)
    {
        return;
    }

    visited++;

    printDescending(node->right, visited);

    std::cout << node->key;

    if (node->color == RED)
    {
        std::cout << "(R)";
    }
    else
    {
        std::cout << "(B)";
    }

    std::cout << " ";

    printDescending(node->left, visited);
}

void RBTree::printDescending(int& visited)
{
    visited = 0;

    printDescending(root, visited);

    std::cout << std::endl;
}


// ======================================
// PRINT TREE
// ======================================

void RBTree::printTree(Node* node, int level)
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

    std::cout << node->key;

    if (node->color == RED)
    {
        std::cout << "(R)";
    }
    else
    {
        std::cout << "(B)";
    }

    std::cout << std::endl;

    printTree(node->left, level + 1);
}

void RBTree::print()
{
    if (root == nullptr)
    {
        std::cout << "(порожнє дерево)" << std::endl;
        return;
    }

    printTree(root, 0);
}


// ======================================
// HEIGHT
// ======================================

int RBTree::getHeight(Node* node)
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

int RBTree::height()
{
    return getHeight(root);
}


// ======================================
// SIZE
// ======================================

int RBTree::getSize(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 +
        getSize(node->left) +
        getSize(node->right);
}

int RBTree::size()
{
    return getSize(root);
}


// ======================================
// CLEAR
// ======================================

void RBTree::clear(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
}

void RBTree::clear()
{
    clear(root);

    root = nullptr;
}


// ======================================
// COPY
// ======================================

void RBTree::copyTree(Node* node, RBTree& tree)
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

void RBTree::copyTo(RBTree& tree)
{
    tree.clear();

    copyTree(root, tree);
}
