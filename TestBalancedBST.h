#pragma once
#include <iostream>
#include "BalancedBST.h"
/**
 * @brief Concrete class extending BalancedBST for testing insertion logic.
 * 
 * @tparam T The data type stored in the tree.
 * @example
 * TestBalancedBST<int> tree;
 * tree.insert(10);
 * tree.insert(5);
 * tree.insert(15);
 * cout << "Tree height: " << tree.getHeight() << endl;
 */
template <class T>
class TestBalancedBST : public BalancedBST<T>
{
    using Node = typename BinarySearchTree<T>::Node;
    using HeightNode = typename BalancedBST<T>::HeightNode;

public:
    /**
     * @brief Inserts a new value into the balanced tree.
     * @param value The value to insert.
     */

    void insert(T value) override
    {
        this->root = insertRec(static_cast<HeightNode *>(this->root), value);
    }

private:
    /**
     * @brief Recursive helper for insertion maintaining node heights.
     * @param node Current node pointer.
     * @param value The value to insert.
     * @return Updated node pointer.
     */
    HeightNode *insertRec(HeightNode *node, T value)
    {
        if (!node)
            return new HeightNode(value);

        if (value < node->key)
            node->left = insertRec(static_cast<HeightNode *>(node->left), value);
        else if (value > node->key)
            node->right = insertRec(static_cast<HeightNode *>(node->right), value);

        node->height = std::max(this->height(static_cast<HeightNode *>(node->left)),
                                this->height(static_cast<HeightNode *>(node->right))) +
                       1;
        return node;
    }
};