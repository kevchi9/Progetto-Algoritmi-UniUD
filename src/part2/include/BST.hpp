#ifndef _BST_H
#define _BST_H

#include "../include/Node.hpp"

class BST{

    private:

    Node* root;

    public:

    BST();

    Node* get_root();

    void set_root(Node* x);

    /**
     * Prints the representation of the tree.
     * @param x The root of each subtree.
     */
    void show(Node *x);

    /**
     * Adds a new Node to the tree with the given root.
     * @param k The key of the new Node.
     * @param v The value of the new Node.
     */
    void BST_insert(Node* z);

    /**
     * Replaces one subtree as a child of its parent with another subtree. 
     * When BST_transplant replaces the subtree rooted at Node u with the subtree rooted at Node v, 
     * Node u's parent becomes node v's parent, and u's parent ends up having v as its child.
     * @param u The subtree to overwrite.
     * @param v The new subtree.
     * @return Root of the updated tree.
     */
    void transplant(Node *u, Node *v);

    /**
     * Finds the minimum of a subtree.
     * @param x Root of the subtree.
     * @return The minimum of the subtree.
     */
    Node* minimum(Node *x);

    /**
     * Finds the Node x with key k in the tree with the given root.
     * @param k Key of the Node to find.
     * @return The Node x.
     */
    Node* find(int k);

    /**
     * This function is not needed for the functioning of the BST.
     * It was added for testing purpose.
     * Finds a node and prints his value.
     * @param k Key of the Node to find.
     */
    std::string find_value(int k);

    /**
     * Removes Node with key k from the tree keeping the BST properties.
     * @param k Key of the node to remove.
     */
    void BST_remove(int k);

    /**
     * Removes all Nodes from the tree, which then becomes empty.
     * @param x The root of each subtree.
     * @return The new root (NULL).
     */
    void clear(Node* root);
    /**
     *  ### ONLY FOR DEBUGGING PURPOSES ###
     */
    void print_info(Node* root);
};

#endif
