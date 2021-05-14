#include "Node.hpp"
#include <iostream>

    Node::Node(int k, std::string v) : key(k), value(v){}

    Node* Node::clone(){
        Node* y = new Node(this->get_key(), this->get_value());
        y->set_parent(this->get_parent());
        y->set_left(this->get_left());
        y->set_right(this->get_right());
        return y;
    }
    
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

        if(this==NULL){
            return 0;
        }

        left = this->get_left()->get_height();
        right = this->get_right()->get_height();
        
        if(left > right){
            return left+1;
        } else {
            return right+1;
        }
    }       