#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include <iostream>
#include <algorithm>
#include <assert.h>


AVL::AVL(): root(nullptr) {};

Node* AVL::get_root() {
    return root;
}

void AVL::set_root(Node* x) {
    root = x;
}

void AVL::show(Node *x) {
    if (x == nullptr){
        std::cout << "NULL" << ' ';
        return;
    } else {
        std::cout << x->get_key() << ':' << x->get_value() << ':' << x->get_height() << ' ';
    }
    show(x->get_left());
    show(x->get_right());
}

int AVL::get_balance(Node* x){

    if (x != nullptr)
    {
        return (x->get_left()->get_height() - x->get_right()->get_height());
    }
    else 
    {
        return 0;
    }
}

void AVL::check_height(Node* root){
    std::cout << root->get_height() << '\n';
}

void AVL::left_rot(Node* x){
    Node *y = x->get_right();
    Node *z = y->get_left();
    Node *p = x->get_parent();
    
    x->set_right(z);
    if(z != NULL){
        z->set_parent(x);
    }

    y->set_left(x);
    x->set_parent(y);
    
    if (x == get_root()){
        assert(p == NULL);
        set_root(y);
    } else {
        if(x == p->get_left()){
            p->set_left(y); 
        } else {
            p->set_right(y);
        }
    }
    y->set_parent(p);
}

void AVL::right_rot(Node* x){
    Node* y = x->get_left();
    Node* z = y->get_right();
    Node* p = x->get_parent();

    x->set_left(z);
    if(z != NULL){
        z->set_parent(x);
    }

    y->set_right(x);
    x->set_parent(y);

    
    if (x == get_root()){
        assert(p == NULL);
        set_root(y);
    } else {
        if(x == p->get_right()){
            p->set_right(y); 
        } else {
            p->set_left(y);
        }
    }
    y->set_parent(p);
}

void AVL::right_left_rot(Node* x){
    Node *y = x->get_right();
    assert(y != NULL);
    Node *z = y->get_left();
    assert(z != NULL);

    right_rot(y);
    left_rot(x);
}

void AVL::left_right_rot(Node*x){
    Node *y = x->get_left();
    assert(y != NULL);
    Node* z = y->get_right();
    assert(z != NULL);

    left_rot(y);
    right_rot(x);
}

void AVL::AVL_insert(Node* z){

    Node* y = nullptr;
    Node* x = get_root();

    if (x == nullptr){ // if tree was empty
        set_root(z);
        return;
    }
    while (x != nullptr){
        y = x;
        if (z->get_key() < x->get_key()){
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
    AVL_balance_helper(get_root());
}

Node* AVL::find(int k){
    Node* x = get_root();

    while(x->get_key() != k && x != nullptr){
        if (x->get_key() > k){
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    return x;
}

std::string AVL::find_value(int k){

    Node* x = get_root();
    while(x != nullptr){
        if (k > x->get_key()){
            x = x->get_right();
        } else if (k < x->get_key()){
            x = x->get_left();
        } else {
            return x->get_value();
            
        }
    }
    return "NULL";
}

void AVL::transplant(Node *u, Node *v) {
    if(u == get_root()){
        if (v != nullptr){
            v->set_parent(u->get_parent());
        }
        set_root(v);
        return;
    } else if (u == u->get_parent()->get_left()) {  // se u è figlio sx
        u->get_parent()->set_left(v);
    } else {
        u->get_parent()->set_right(v); 
    } if (v != nullptr) {
        v->set_parent(u->get_parent());
    }
    u->set_parent(nullptr);
}

void AVL::AVL_remove(int k){
    Node* z = find(k);
    if (z->get_left() == nullptr){          // il nodo da rimuovere non ha figlio sx
        transplant(z, z->get_right());
    } else if (z->get_right() == nullptr){  // non ha figlio dx
        transplant(z, z->get_left());
    } else {                                // ha entrambi i figli
        Node* y = minimum(z->get_right());  // cerco il successore
        if (y->get_parent() != z){          // il minimo non è direttamente collegato a z
            transplant(y, y->get_right());
            y->set_right(z->get_right());
            if (y->get_right() != nullptr){
                y->get_right()->set_parent(y);
            }
        }  

        transplant(z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);
    }
    //Node* p = z->get_parent();
    delete z;
    //AVL_balance(p);
    AVL_balance_helper(get_root());
}

void AVL::AVL_balance_helper(Node* x){
    if(x != nullptr){
        AVL_balance_helper(x->get_left());
        AVL_balance_helper(x->get_right());
        AVL_balance(x);
    }
}

void AVL::AVL_balance(Node* x) {

    Node* left = x->get_left();
    Node* right = x->get_right();

    if(x != nullptr) 
    {
        if (left->get_height() > right->get_height() + 1)
        {
            if (left->get_left()->get_height() >= left->get_right()->get_height()) // rotations on left subtree
            {
                right_rot(x);
            } 
            
            else

            {
                left_right_rot(x);
            }
        } 
        else if (1 + left->get_height() < right->get_height() ) 
        {
            if (right->get_right()->get_height() >= right->get_left()->get_height()) // rotations on right subtree
            {
                left_rot(x);
            }
            else 
            {
                right_left_rot(x);
            }
        } 
        else if (get_balance(left) > 1) 
        {
            AVL_balance(left);
        }
        else if (get_balance(right) > 1) 
        {
            AVL_balance(right);
        }
    }
}

void AVL::clear(Node *x) {

    if (x == nullptr){
        set_root(x);
        return;
    }
    clear(x->get_left());
    clear(x->get_right());
    delete x;
    x = nullptr;
    return;
}


/*
insert 8 eight
insert 4 four
insert 10 ten
remove 10
insert 16 sixteen
insert 12 twelve
insert 14 fourteen
insert 17 seventeen
remove 4
insert 1 one
remove 8
insert 5 five
insert 18 eighteen
insert 19 nineteen
insert 9 nine
remove 9
insert 13 thirteen
insert 3 three
insert 7 seven
remove 7
remove 13
insert 2 two
remove 5
show

*/
