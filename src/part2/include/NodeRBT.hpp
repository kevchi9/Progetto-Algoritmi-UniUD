#ifndef _NODERBT_H
#define _NODERBT_H

#include <string>
enum node_color
{
    BLACK = 0,
    RED = 1,
};

class NodeRBT
{

private:
    int key;
    std::string value;
    NodeRBT *parent = nullptr;
    NodeRBT *left = nullptr;
    NodeRBT *right = nullptr;
    enum node_color color = BLACK;

public:
    /**
     * Constructor for Node class.
     * @param k Data of the new Node.
     * @param v Extra data of the new Node.
     */
    NodeRBT(int k, std::string &v);

    void set_parent(NodeRBT *x);

    void set_left(NodeRBT *x);

    void set_right(NodeRBT *x);

    void set_color(enum node_color node_color);

    int get_key() const;

    std::string get_value() const;

    NodeRBT *get_parent();

    NodeRBT *get_uncle();

    NodeRBT *get_left();

    NodeRBT *get_right();

    enum node_color get_color() const;

    bool is_red_child_red();
};

#endif