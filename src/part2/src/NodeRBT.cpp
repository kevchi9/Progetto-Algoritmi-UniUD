#include "../include/NodeRBT.hpp"
#include <string>
#include <iostream>

NodeRBT::NodeRBT(int k, std::string v) : key(k), value(v)
{
    enum node_color color = BLACK;
}

void NodeRBT::set_parent(NodeRBT* x) 
{
    parent = x;
}

NodeRBT* NodeRBT::get_parent()
{
    return parent;
}

NodeRBT* NodeRBT::get_uncle()
{
    NodeRBT* grandp = this->get_parent()->get_parent();
    if (this->get_parent() == grandp->get_left()) 
    {
        return grandp->get_right();
    } 
    else 
    {
        return grandp->get_left();
    }
}

void NodeRBT::set_left(NodeRBT* x)
{
    left = x;
}

NodeRBT* NodeRBT::get_left()
{
    return left;
}

void NodeRBT::set_right(NodeRBT* x)
{
    right = x;
}

NodeRBT* NodeRBT::get_right()
{
    return right;
}

int NodeRBT::get_key()
{
    return key;
}

std::string NodeRBT::get_value()
{
    return value;
}

node_color NodeRBT::get_color()
{
    return color;
}

void NodeRBT::set_color(enum node_color c) 
{
    color = c;
}

bool NodeRBT::is_red_child_red()
{
    if(this->get_color() != RED) 
    {
        std::cout << "X non è rosso";
        return false;
    }
    return this->get_color() == this->get_parent()->get_color();
}
