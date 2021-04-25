#include "AVL.hpp"
#include "BST.hpp"                  // imported for the BST's basic functions
#include <iostream>
#include <algorithm>

unsigned int AVL::get_balance(Node* x){
    if (x != nullptr){
        return (x->get_left()->get_height() - x->get_right()->get_height());
    }
}

Node* AVL::right_rotate(Node* x){

    Node* temp;
    temp = x->get_right();
    x->set_right(temp->get_left());
    temp->set_left(x);
    return temp; 
}

Node* AVL::left_rotate(Node* x){

    Node* temp;
    temp = x->get_left();
    x->set_right(temp->get_left());
    temp->set_left(x);
    return temp;
}

Node* AVL::AVL_Insert(Node* root, int k, std::string v){
    if (root == nullptr){
        root = new Node(k,v);
        root->increase_height(); 
    }
    if (root->get_key() > k){
        root->set_left(AVL_Insert(root->get_left(), k, v));
    } else {
        root->set_right(AVL_Insert(root->get_right(), k, v));
    } 
    // updates the node height
    root->set_height(std::max(root->get_left()->get_height(), root->get_right()->get_height()) + 1);
    int balance_difference = get_balance(root);
    // checks if the subtrees are balanced and fixes them
    if ( balance_difference > 1 && k < root->get_left()->get_key()) {
        return right_rotate(root);
    } else if (balance_difference < -1 && k > root->get_right()->get_key()) {
        return left_rotate(root);
    } else if (balance_difference > 1 && k > root->get_left()->get_key()){
        root->set_left(left_rotate(root->get_left()));
        return right_rotate(root);
    } else if (balance_difference < -1 && k < root->get_right()->get_key()){
        root->set_right(right_rotate(root->get_right()));
        return left_rotate(root);
    }
    return root;
}

Node* AVL::AVL_Remove(Node* root, int k){
    return root;
}