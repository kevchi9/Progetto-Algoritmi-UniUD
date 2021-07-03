#ifndef _AVL_H
#define _AVL_H

#include <string.h>
#include "../include/Node.hpp"
#include "../include/BST.hpp"
class AVL : public BST
{

private:
    Node *root;

public:
    AVL();

    Node *get_root();

    void set_root(Node *x);
    /**
     * Prints the representation of the tree.
     * @param x The root of each subtree
     */
    void show(Node *x);

    /**
     * Calculates the height difference between two subtree
     * @param x The root of the two subtree.
     * @return Value of the difference. 
     */
    int get_balance(Node *x);

    /**
     * Does a left rotation on Node x.
     * @param x Node used as pin.
     */
    void left_rot(Node *x);

    /**
     * Does a right rotation on Node x.
     * @param x Node used as pin.
     */
    void right_rot(Node *x);

    void right_left_rot(Node *x);

    void left_right_rot(Node *x);
    /**
     * Adds a new Node to the tree with the given root and then returns the tree's root.
     * @param z The new node;
     */
    int insert_and_balance(Node *x, Node *p, Node *y);

    void insert_helper(Node *x, Node *p, Node *y);

    void insert(Node *x);

    Node *find(int k);

    void transplant(Node *u, Node *v);

    /**
     * Removes Node with key k from the tree keeping the AVL properties.
     * @param root Root of the tree.
     * @param k Key of the node to remove.
     * @return The new root.
     */
    void remove(int k);

    /**
     * Checks if the tree is balanced after an insertion and fixes it.
     * @param x Root of the tree.
     * @return The new root.
     */
    void balance(Node *x);

    void balance_helper(Node *x);

    /**
     * Calculates heights of the root's subtrees
     */
    void check_height(Node *x);

    void clear(Node *x);

    std::string find_value(int k);

    void fix_height(Node *x);
};

#endif