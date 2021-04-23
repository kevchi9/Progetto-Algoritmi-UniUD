#ifndef _NODE_H
#define _NODE_H

#include <string>

class Node{

private:
    int key;
    std::string value;
    Node *parent = nullptr;
    Node *left = nullptr; 
    Node *right = nullptr;

public:
    Node(int k, std::string v);
    Node();
    void set_parent(Node* x);
    void set_left(Node* x);
    void set_right(Node* x);
    int get_key();
    std::string get_value();
    Node* get_parent();
    Node* get_left();
    Node* get_right();
};

#endif