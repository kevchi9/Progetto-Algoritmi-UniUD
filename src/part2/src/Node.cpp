#include "../include/Node.hpp"
#include <iostream>

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


    int Node::get_height() {
        
        int left, right;

        if (this == nullptr){
            return 0;
        }

        left = this->get_left()->get_height();
        right = this->get_right()->get_height();
        
        if (left > right){
            return left+1;
        } else {
            return right+1;
        }
    }       