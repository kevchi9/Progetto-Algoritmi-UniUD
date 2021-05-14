#ifndef _AVL_H
#define _AVL_H

#include <string.h>
#include "Node.hpp"
#include "BST.hpp"
class AVL : public BST {

    public:

    /**
     * Prints the representation of the tree.
     * @param x The root of each subtree
     */
    void show(Node *x);

    /**
     * Calculates the height difference between two subtree
     * @param root The root of the two subtree.
     * @return Value of the difference. 
     */
    int get_balance(Node* root);

    /**
     * Does a left rotation on Node x.
     * @param x Node used as pin.
     * @return The new root.
     */
    Node* left_rot(Node* x);

    /**
     * Does a right rotation on Node x.
     * @param x Node used as pin.
     * @return The new root.
     */
    Node* right_rot(Node* x);

    /**
     * Adds a new Node to the tree with the given root and then returns the tree's root.
     * @param root That identifies the tree.
     * @param k The key of the new Node.
     * @param v The value of the new Node.
     * @return The root
     */
    Node* AVL_insert(Node* root, int k, std::string v);

    /**
     * Removes Node with key k from the tree keeping the AVL properties.
     * @param root Root of the tree.
     * @param k Key of the node to remove.
     * @return The new root.
     */
    Node* AVL_remove(Node* root, int k);

    /**
     * Checks if the tree is balanced after an insertion and fixes it.
     * @param root Root of the tree.
     * @return The new root.
     */
    Node* AVL_balance(Node* root);

    /**
     *  ### ONLY FOR DEBUGGING PURPOSES ###
     */
    void print_info(Node* root);

    /**
     * Calculates heights of the root's subtrees
     */
    void check_height(Node* root);

};

#endif