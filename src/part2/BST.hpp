#ifndef _BST_H
#define _BST_H

#include "Node.hpp"

class BST{

    public:

    /**
     * Prints the representation of the tree.
     * @param x The root of each subtree.
     */
    void show(Node *x);

    /**
     * Adds a new Node to the tree with the given root.
     * @param root Root.
     * @param k The key of the new Node.
     * @param v The value of the new Node.
     * @return The new root.
     */
    Node* BST_insert(Node *root, int k, std::string v);

    /**
     * Replaces one subtree as a child of its parent with another subtree. 
     * When BST_transplant replaces the subtree rooted at Node u with the subtree rooted at Node v, 
     * Node u's parent becomes node v's parent, and u's parent ends up having v as its child.
     * @param root Root of the tree.
     * @param u The subtree to overwrite.
     * @param v The new subtree.
     * @return Root of the updated tree.
     */
    Node* transplant(Node *root, Node *u, Node *v);

    /**
     * Finds the minimum of a subtree.
     * @param x Root of the subtree.
     * @return The minimum of the subtree.
     */
    Node* minimum(Node *x);

    /**
     * Finds the Node x with key k in the tree with the given root.
     * @param root Root of the tree.
     * @param k Key of the Node to find.
     * @return The Node x.
     */
    Node* find(Node *root, int k);

    /**
     * This function is not needed for the functioning of the BST.
     * It was added for testing purpose.
     * Finds a node and prints his value.
     * @param root Root of the tree.
     * @param k Key of the Node to find.
     */
    void find_value(Node* root, int k);

    /**
     * Removes Node with key k from the tree keeping the BST properties.
     * @param root Root of the tree.
     * @param k Key of the node to remove.
     * @return The new root.
     */
    Node* BST_remove(Node *root, int k);

    /**
     * Removes all Nodes from the tree, which then becomes empty.
     * @param x The root of each subtree.
     * @return The new root (NULL).
     */
    Node* clear(Node *x);

    void print_info(Node* root);
};

#endif
