#ifndef _AVL_H
#define _AVL_H

#include <string.h>
#include "Node.hpp"
#include "BST.hpp"
class AVL : public BST {

    public:

    /**
     * Calculates the height difference between two subtree
     * @param root The root of the two subtree.
     * @return Value of the difference. 
     */
    unsigned int get_balance(Node* root);

    /**
     * Does a right rotation on Node x.
     * @param x Node used as pin.
     * @return The new root.
     */
    Node* right_rotate(Node* x);

    /**
     * Does a left rotation on Node x.
     * @param x Node used as pin.
     * @return The new root.
     */
    Node* left_rotate(Node* x);

    /**
     * Adds a new Node to the tree with the given root and then returns the tree's root.
     * @param root That identifies the tree.
     * @param k The key of the new Node.
     * @param v The value of the new Node.
     * @return The root
     */
    Node* AVL_Insert(Node* root, int k, std::string v);

    /**
     * Removes Node with key k from the tree keeping the AVL properties.
     * @param root Root of the tree.
     * @param k Key of the node to remove.
     * @return The new root.
     */
    Node* AVL_Remove(Node* root, int k);

};

#endif