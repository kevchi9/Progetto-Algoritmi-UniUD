#include "Node.hpp"
#include "BST.hpp"
#include <iostream>


void BST::show(Node *x) {
    if (x == nullptr){
        std::cout << "NULL" << ' ';
        return;
    } else {
        std::cout << x->get_key() << ':' << x->get_value() << ' ';
    }
    show(x->get_left());
    show(x->get_right());
    std::cout << '\n';
}

void BST::BST_insert(Node *root, int k, std::string& v){
    Node* y = nullptr;
    Node* x = root;
    Node* z = new Node(k, v);
    if (root == nullptr){ // if tree was empty
        root = z;
        std::cout << "Root updated \n";
        show(root);
        return;
    }
    while (x != nullptr){
        y = x;
        if (k < x->get_key()){
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    z->set_parent(y);
    if (z->get_key() < y->get_key()){
        y->set_left(z);
    } else { 
        y->set_right(z);
    }
}

Node* BST::transplant(Node *root, Node *u, Node *v) {
    if(u->get_parent() == nullptr){
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->set_left(v);
    } else {
        u->get_parent()->set_right(v);
    } if (v != nullptr) {
        v->set_parent(u->get_parent());
    }
    return root;
}

Node* BST::BST_remove(Node *root, int k){
    Node* z = find(root, k);
    
    if (z->get_left() == nullptr){
        root = transplant(root, z, z->get_right());
    } else if (z->get_right() == nullptr){
        root = transplant(root, z, z->get_left());
    } else {
        Node* y = minimum(z->get_right());
        if (y->get_parent() != z){
            root = transplant(root, y, y->get_right());
            y->set_right(z->get_right());
            y->get_right()->set_parent(y);
        }
        root = transplant(root, z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);
    }
    return root;
}

Node* BST::minimum(Node *x){
    while (x->get_left() != nullptr){
        x = x->get_left();
    }
    return x;
}

Node* BST::find(Node *root, int k){
    Node* x = root;
    while(x->get_key() != k){
        if (x->get_key() > k){
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    return x;
}

void BST::find_value(Node* root, int k){
    
    if (k > root->get_key()){
        find_value(root->get_right(), k);
    } else if (k < root->get_key()){
        find_value(root->get_left(), k);
    } else {
        std::cout << root->get_value() << '\n';
    }
}

Node* BST::clear(Node *x) {
    if (x == nullptr){
        return x;
    }
    clear(x->get_left());
    clear(x->get_right());
    delete x;
    x = nullptr;
    return x;
}