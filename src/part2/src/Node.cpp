#include "../include/Node.hpp"
#include <iostream>

    Node::Node(int k, std::string v) : key(k), value(v), height(1){}
 
    void Node::set_parent(Node* x) 
    {
        parent = x;
    }

    Node* Node::get_parent()
    {
        return parent;
    }

    void Node::set_left(Node* x)
    {
        left = x;
    }

    Node* Node::get_left()
    {
        return left;
    }

    void Node::set_right(Node* x)
    {
        right = x;
    }

    void Node::decrease_height()
    {
        height--;
    }

    void Node::increase_height()
    {
        height++;
    }

    Node* Node::get_right()
    {
        return right;
    }

    int Node::get_key()
    {
        return key;
    }

    std::string Node::get_value()
    {
        return value;
    }

    int Node::get_height()
    {
        return height;
    }

    void Node::set_height(int k){
        height = k;
    }
    /*
    int Node::get_height() {
        
        int left = 0;
        int right = 0;

        Node* left_node = this->get_left();
        Node* right_node = this->get_right();

        if (left_node != nullptr)
        {
            left = left_node->get_height(); 
        }

        if (right_node != nullptr)
        {
            right = right_node->get_height(); 
        }
        
        if (left > right){
            return left+1;
        } else {
            return right+1;
        }
    }    
    */   