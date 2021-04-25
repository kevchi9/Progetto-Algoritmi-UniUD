#include "Node.hpp"

    Node::Node(int k, std::string v) : key(k), value(v){}
    
    void Node::set_parent(Node* x) {
        parent = x;
    }

    Node* Node::get_parent(){
        return parent;
    }

    void Node::set_left(Node* x){
        left = x;
    }

    Node* Node::get_left(){
        return left;
    }

    void Node::set_right(Node* x){
        right = x;
    }

    Node* Node::get_right(){
        return right;
    }

    int Node::get_key(){
        return key;
    }

    std::string Node::get_value(){
        return value;
    }

    unsigned int Node::get_height(){
        return height;
    }

    void Node::set_height(unsigned int k){
        height = k;
    }

    void Node::increase_height(){
        height++;
    }

    void Node::decrease_height(){
        height--;
    }