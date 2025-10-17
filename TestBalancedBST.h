#pragma once
#include <iostream>
#include "BalancedBST.h"

template <class T>
class TestBalancedBST : public BalancedBST<T>
{
    using Node = typename BinarySearchTree<T>::Node;
    using HeightNode = typename BalancedBST<T>::HeightNode;

public:
    void insert(T value) override
    {
        this->root = insertRec(static_cast<HeightNode *>(this->root), value);
    }

private:
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