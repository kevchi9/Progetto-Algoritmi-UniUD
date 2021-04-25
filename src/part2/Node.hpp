#ifndef _NODE_H
#define _NODE_H

#include <string>

class Node{

private:
    const int key;
    unsigned int height = 1;
    const std::string value;
    Node *parent = nullptr;
    Node *left = nullptr; 
    Node *right = nullptr;

public:
    Node(int k, std::string v);
    void set_parent(Node* x);
    void set_left(Node* x);
    void set_right(Node* x);
    int get_key();
    std::string get_value();
    Node* get_parent();
    Node* get_left();
    Node* get_right();
    unsigned int get_height();
    void set_height(unsigned int k);
    void increase_height(); //TODO: rivedere, non modifica il valore di height dei nodi superiori a quell puntato.
    void decrease_height();
};

#endif