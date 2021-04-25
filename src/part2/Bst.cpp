#include "Node.hpp"
#include "BST.hpp"
#include <iostream>


void BST::Show(Node *x) {
    if (x == nullptr){
        std::cout << "NULL" << ' ';
        return;
    } else {
        std::cout << x->get_key() << ':' << x->get_value() << ' ';
    }
    Show(x->get_left());
    Show(x->get_right());
    std::cout << '\n';
}

void BST::BST_Insert(Node *root, int k, std::string& v){
    Node* y = nullptr;
    Node* x = root;
    Node* z = new Node(k, v);
    if (root == nullptr){ // if tree was empty
        root = z;
        std::cout << "Root updated \n";
        Show(root);
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

Node* BST::Transplant(Node *root, Node *u, Node *v) {
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

Node* BST::BST_Remove(Node *root, int k){
    Node* z = Find(root, k);
    
    if (z->get_left() == nullptr){
        root = Transplant(root, z, z->get_right());
    } else if (z->get_right() == nullptr){
        root = Transplant(root, z, z->get_left());
    } else {
        Node* y = Minimum(z->get_right());
        if (y->get_parent() != z){
            root = Transplant(root, y, y->get_right());
            y->set_right(z->get_right());
            y->get_right()->set_parent(y);
        }
        root = Transplant(root, z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);
    }
    return root;
}

Node* BST::Minimum(Node *x){
    while (x->get_left() != nullptr){
        x = x->get_left();
    }
    return x;
}

Node* BST::Find(Node *root, int k){
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

void BST::Find_Value(Node* root, int k){
    
    if (k > root->get_key()){
        Find_Value(root->get_right(), k);
    } else if (k < root->get_key()){
        Find_Value(root->get_left(), k);
    } else {
        std::cout << root->get_value() << '\n';
    }
}

Node* BST::Clear(Node *x) {
    if (x == nullptr){
        return x;
    }
    Clear(x->get_left());
    Clear(x->get_right());
    delete x;
    x = nullptr;
    return x;
}
