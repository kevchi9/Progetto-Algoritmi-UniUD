#include "Node.hpp"
#include "Bst.hpp"
#include <iostream>

void BST_Show(Node *x) {
    if (x == nullptr){
        std::cout << "NULL" << ' ';
        return;
    } else {
        std::cout << x->get_key() << ':' << x->get_value() << ' ';
    }
    BST_Show(x->get_left());
    BST_Show(x->get_right());
    std::cout << '\n';
}

void BST_Insert(Node *root, int k, std::string& v){
    Node* y = nullptr;
    Node* x = root;
    Node* z = new Node(k, v);
    if (root == nullptr){ // if tree was empty
        root = z;
        std::cout << "Root updated \n";
        BST_Show(root);
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

void BST_Transplant(Node *root, Node *u, Node *v) {
    if(u->get_parent() == nullptr){
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->set_left(v);
    } else {
        u->get_parent()->set_right(v);
    } if (v != nullptr) {
        v->set_parent(u->get_parent());
    }
}

Node* BST_Minimum(Node *x){
    while (x->get_left() != nullptr){
        x = x->get_left();
    }
    return x;
}

Node* BST_Find(Node *root, int k){
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

void BST_Remove(Node *root, int k){
    Node* z = BST_Find(root, k);
    
    if (z->get_left() == nullptr){
        BST_Transplant(root, z, z->get_right());
    } else if (z->get_right() == nullptr){
        BST_Transplant(root, z, z->get_left());
    } else {
        Node* y = BST_Minimum(z->get_right());
        if (y->get_parent() != z){
            BST_Transplant(root, y, y->get_right());
            y->set_right(z->get_right());
            y->get_right()->set_parent(y);
        }
        BST_Transplant(root, z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);

    }
}

void BST_Clear(Node *x) {
    if (x == nullptr){
        return;
    }
    BST_Clear(x->get_left());
    BST_Clear(x->get_right());
    delete x;
    x = nullptr;
}

int main(){
    std::string input;
    int k;
    std::string v;
    Node* root = nullptr;
    do {
        std::cin >> input;
        switch (input[0]) {
        case 'i':
            std::cin >> k;
            std::cin >> v;
            if (root == nullptr){
                root = new Node(k, v);
            } else {
                BST_Insert(root, k, v);
            }
            break;
        case 's':
            BST_Show(root);
            break;
        case 'r':
            std::cin >> k;
            BST_Remove(root,k);
            break;
        case 'f':
            std::cin >> k;
            BST_Find(root,k);
            break;
        case 'c':
            BST_Clear(root);
            break;
        case 'e':
            exit(0);
        default:
            std::cout << "Comando non riconosciuto\n"; 
            break;
        }
    } while(true);
}
