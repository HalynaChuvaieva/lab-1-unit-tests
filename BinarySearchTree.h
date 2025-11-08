#pragma once
#include <iostream>
#include "BalancedBST.h"
using namespace std;

/**
 * @brief Template class implementing a basic Binary Search Tree (BST).
 * 
 * @tparam T The data type stored in the tree.
 * @example
 * BinarySearchTree<int> bst;
 * bst.insert(5);
 * bst.insert(3);
 * bst.insert(7);
 * bst.display(); // Output: 3 5 7
 */
template <class T>
class BinarySearchTree
{
protected:
    /**
     * @brief Internal structure representing a single tree node.
     */
    struct Node
    {
        T key;        ///< Node value.
        Node *left;   ///< Pointer to the left child.
        Node *right;  ///< Pointer to the right child.

        /**
         * @brief Constructs a new node.
         * @param val The value stored in the node.
         */
        Node(T val) : key(val), left(nullptr), right(nullptr) {}
    };
    Node *root; ///< Pointer to the root of the tree.


    /**
     * @brief Inserts a new key into the subtree rooted at @p node.
     * @param node The current node.
     * @param key The value to insert.
     * @return The updated subtree root.
     */
    virtual Node *insert(Node *node, T key)
    {
        if (!node)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    /**
     * @brief Finds the node with the minimum key in a subtree.
     * @param node Root of the subtree.
     * @return Pointer to the node with the smallest key.
     */
    Node *minValue(Node *node)
    {
        Node *current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    /**
     * @brief Deletes a node with the specified key.
     * @param node The current subtree root.
     * @param key The key to remove.
     * @return Pointer to the updated subtree root.
     */
    Node *deleteNode(Node *node, T key)
    {
        if (!node)
            return node;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            Node *temp = minValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    /**
     * @brief Performs inorder traversal and prints all node keys.
     * @param node Current node.
     */
    void inorder(Node *node)
    {
        if (node)
        {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

public:
    /// @brief Constructs an empty Binary Search Tree.
    BinarySearchTree() : root(nullptr) {}
    /**
     * @brief Inserts a new element into the tree.
     * @param key Value to insert.
     */
    virtual void insert(T key) { root = insert(root, key); }
    /**
     * @brief Removes an element from the tree.
     * @param key Value to remove.
     */
    void remove(T key) { root = deleteNode(root, key); }
    /**
     * @brief Prints all elements of the tree in sorted order.
     */
    void display()
    {
        inorder(root);
        cout << endl;
    }
};
