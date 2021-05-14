#include "Node.hpp"
#include "AVL.hpp"
#include "BST.hpp"                  // imported for the BST's basic functions
#include <iostream>
#include <algorithm>

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
    if (x != nullptr){
        return (abs(x->get_left()->get_height() - x->get_right()->get_height()));
    } else {
        return 0;
    }
}

void AVL::check_height(Node* root){
    std::cout << root->get_height() << '\n';
}

Node* AVL::left_rot(Node* x){
    Node* p = x->clone();
    Node *tp = p->get_right()->clone();

    p->set_right(tp->get_left());
    tp->set_left(p);
    tp->set_parent(p->get_parent());
    p->set_parent(tp);

    return tp;
}

Node* AVL::right_rot(Node* x){
    Node* p = x->clone();
    Node* tp = p->get_left()->clone();

    p->set_left(tp->get_right());
    tp->set_right(p);
    tp->set_parent(p->get_parent());
    p->set_parent(tp);

    return tp;
}

Node* AVL::AVL_insert(Node* root, int k, std::string v){
    if (root == nullptr){
        root = new Node(k,v);
        return root;
    }else if (root->get_key() > k){
        root->set_left(AVL_insert(root->get_left(), k, v));
        root->get_left()->set_parent(root);
    } else {
        root->set_right(AVL_insert(root->get_right(), k, v));
        root->get_right()->set_parent(root);
    } 
    root = AVL_balance(root);
    return AVL_balance(root);
}
//  TODO: se bilancia un sotto albero poi non torna ai piani superiori a controllare l'altezza
Node* AVL::AVL_balance(Node* root){
    if(root != nullptr){
        if (root->get_left()->get_height() > root->get_right()->get_height() + 1){
            Node* left = root->get_left();
            if (left->get_left()->get_height() > left->get_right()->get_height()){
                root = right_rot(root);
            } else {
                root->set_left(left_rot(left));
                root = right_rot(root);
            }
        } else if (1 + root->get_left()->get_height() < root->get_right()->get_height() ) {
            Node* right = root->get_right();
            if (right->get_right()->get_height() > right->get_left()->get_height()){
                root = left_rot(root);
            } else {
                root->set_right(right_rot(right));
                root = left_rot(root);
            }
        } else if (get_balance(root->get_left()) > 1) {
            root->set_left(AVL_balance(root->get_left()));
        } else if (get_balance(root->get_right()) > 1) {
            root->set_right(AVL_balance(root->get_right()));
        }
        return root;
    } else {
        return nullptr;
    }
}

/*
Node* AVL::AVL_balance_insertion(Node* root, int k){
    int balance_difference = get_balance(root);

    // checks if the tree is balanced and fixes it
    if ( balance_difference > 1 && k < root->get_left()->get_key()) {
        std::cout << "RIGHT Rotation\n";
        return right_rot(root);
    } else if (balance_difference < -1 && k > root->get_right()->get_key()) {
        std::cout << "LEFT Rotation\n";
        return left_rot(root);
    } else if (balance_difference > 1 && k > root->get_left()->get_key()){
        std::cout << "LEFT-RIGHT Rotation\n";
        return lr_rot(root);
    } else if (balance_difference < -1 && k < root->get_right()->get_key()){
        std::cout << "RIGHT-LEFT Rotation\n";
        return rl_rot(root);
    }
    return root;
}
*/

void AVL::print_info(Node* root){
    if (root != nullptr){
        std::cout << "\nNodo " << root->get_key() << '\n';
        std::cout << "Parent = ";
        if (root->get_parent() != nullptr){
        std::cout << root->get_parent()->get_key() << '\n';
        } else {
            std::cout << "NULL\n";
        }
        std::cout << "Left = ";
        if (root->get_left() != nullptr){
            std::cout << root->get_left()->get_key() << '\n';
        } else {
            std::cout << "NULL\n";
        }
        std::cout << "Right = ";
        if (root->get_right() != nullptr){
            std::cout << root->get_right()->get_key() << '\n';
        } else {
            std::cout << "NULL\n";
        }
        std::cout << "\n__________________\n";
        print_info(root->get_left());
        print_info(root->get_right());
    }
}
// transplant sovrascrive il terzo parametro al secondo, il secondo parametro viene perso.

//TODO: quando eseguo la sequenza di istruzioni commentata a fine file, l'albero va in loop con il 6.
Node* AVL::AVL_remove(Node *root, int k){
    Node* z = find(root, k);
    Node* p = z->get_parent(); // RIVEDERE QUESTO
 
    if (z->get_left() == nullptr){
        root = transplant(root, z, z->get_right()); // se z non ha figlio sx
    }
    else if (z->get_right() == nullptr){
        root = transplant(root, z, z->get_left());  // se z non ha figlio dx
    } else {                                          // se ha entrambi i figli
        Node* y = minimum(z->get_right());
        if (y->get_parent() != z){
            root = transplant(root, y, y->get_right());
            std::cout << "check 1 \n";
            y->set_right(z->get_right());
            z->get_right()->set_parent(y);
            std::cout << "check 2\n";
        }
        root = transplant(root, z, y);
        y->set_left(z->get_left());

        y->get_left()->set_parent(y);
    }
    print_info(root);
    root = AVL_balance(root);
    std::cout << "check 5s\n";
    return AVL_balance(root);
}



/*

insert 10 ten
insert 4 four
insert 16 sixteen
remove 10
insert 3 three
insert 2 two
insert 6 six
insert 9 nine

*/