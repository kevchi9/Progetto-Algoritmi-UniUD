#ifndef _NODE_H
#define _NODE_H

#include <string>

class Node
{

private:
    const int key;
    const std::string value;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    int height;

public:
    /**
     * Constructor for Node class.
     * @param k Data of the new Node.
     * @param v Extra data of the new Node.
     */
    Node(int k, std::string &v);

    /**
     * Changes value of Node's parent.
     * @param x The new parent.
     */
    void set_parent(Node *x);

    /**
     * Changes value of Node's left.
     * @param x The new left.
     */
    void set_left(Node *x);

    /**
     * Changes value of Node's right.
     * @param x The new right.
     */
    void set_right(Node *x);

    /**
     * Gives back value of Node's height.
     * @return x.height.
     */
    int get_height() const;

    /**
     * Changes value of Node's height.
     * @param k The new height.
     */
    void set_height(int k);
    /**
     * Decreases Node's height by one.
     */
    void decrease_height();

    /**
     * Increases Node's height by one.
     */
    void increase_height();

    /**
     * Gives back value of Node's key.
     * @return Node's key.
     */
    int get_key() const;

    /**
     * Gives back value of Node's value.
     * @return Node's value.
     */
    std::string get_value() const;

    /**
     * Gives back value of Node's parent.
     * @return Node's parent.
     */
    Node *get_parent();

    /**
     * Gives back value of Node's left.
     * @return Node's left.
     */
    Node *get_left();

    /**
     * Gives back value of Node's rigth.
     * @return Node's right.
     */
    Node *get_right();

    //void set_height(unsigned int k);
};

#endif