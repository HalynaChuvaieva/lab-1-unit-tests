#include <iostream>
using namespace std;
#include "BinarySearchTree.h"

/**
 * @brief Abstract class for self-balancing Binary Search Trees.
 * 
 * @tparam T The data type stored in the tree.
 */
template <class T>
class BalancedBST : public BinarySearchTree<T>
{
protected:
    /**
     * @brief Node structure with an additional height field.
     */
    struct HeightNode : public BinarySearchTree<T>::Node
    {
        int height; ///< Node height.
        /**
         * @brief Constructs a HeightNode.
         * @param val The node value.
         */
        HeightNode(T val) : BinarySearchTree<T>::Node(val), height(1) {}
    };

     /**
     * @brief Returns the height of a node.
     * @param node Pointer to the node.
     * @return The height of the node or 0 if null.
     */
    int height(HeightNode *node)
    {
        return node ? node->height : 0;
    }

    /**
     * @brief Pure virtual insert method to be implemented by subclasses.
     * @param value Value to insert.
     */
    virtual void insert(T value) = 0;

public:
    BalancedBST() : BinarySearchTree<T>() {}
    virtual ~BalancedBST() {}
    
    /**
     * @brief Calculates the overall height of the tree.
     * @return Height of the entire tree.
     */
    int getHeight()
    {
        return getHeight(static_cast<HeightNode *>(this->root));
    }

private:
    int getHeight(HeightNode *node)
    {
        if (!node)
            return 0;
        return max(getHeight(static_cast<HeightNode *>(node->left)),
                   getHeight(static_cast<HeightNode *>(node->right))) +
               1;
    }
};