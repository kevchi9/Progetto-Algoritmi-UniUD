#include "../include/RBT.hpp"
#include "assert.h"
#include <iostream>

RBT::RBT(): root(nullptr) {}

void RBT::set_root(NodeRBT* x) {
    root = x;
    root->set_color(NodeRBTColor::BLACK);
    assert(root->get_color() == NodeRBTColor::BLACK);
}

NodeRBT* RBT::get_root() {
    return root;
}

void RBT::RBT_Show(NodeRBT *x){
    if (x == nullptr){
        std::cout << "NULL" << ' ';
        return;
    } else {
        std::cout << x->get_key() << ":" << x->get_value() << ":" << (x->get_color() == NodeRBTColor::RED ? "red" : "black") << ' ';
    }
    
    RBT_Show(x->get_left());
    RBT_Show(x->get_right());
}

void RBT::RBT_Insert(int k, std::string v){
    NodeRBT* new_node = new NodeRBT(k, v);

    if(get_root() == nullptr) {
        set_root(new_node);
        return;
    }

    NodeRBT* upper = nullptr;
    NodeRBT* lower = get_root();

    while(lower != nullptr) {
        upper = lower;
        if (k < lower->get_key()){
            lower = lower->get_left();
        } else {
            lower = lower->get_right();
        }
    }

    new_node->set_color(NodeRBTColor::RED);

    new_node->set_parent(upper);
    if (new_node->get_key() < upper->get_key()){
        upper->set_left(new_node);
    } else { 
        upper->set_right(new_node);
    }
    RBT_InsertFix(new_node);
}

void RBT::RBT_InsertFix(NodeRBT* new_node) {

    if(new_node->get_parent() == nullptr) 
    {
        new_node->set_color(NodeRBTColor::BLACK);
        return;
    } 
    
    else if(new_node->get_parent()->get_color() == NodeRBTColor::BLACK)
    {
        return;
    }

    else if((new_node->is_red_child_red()) && (new_node->get_uncle() == nullptr ? false : (new_node->get_uncle()->get_color() == NodeRBTColor::RED))) // padre e zio rosso
    {
        NodeRBT* next_node = RBT_Insert_PRed_URed(new_node);
        return RBT_InsertFix(next_node);
    }
    else if((new_node->is_red_child_red()) && (new_node->get_uncle() == nullptr ? true : (new_node->get_uncle()->get_color() == NodeRBTColor::BLACK))) // padre rosso e zio nero
    {
        RBT_Insert_PRed_UBlack(new_node);
    }
}
 
NodeRBT* RBT::RBT_Insert_PRed_URed(NodeRBT* new_node) {

    NodeRBT* parent = new_node->get_parent();
    NodeRBT* uncle = new_node->get_uncle();
    NodeRBT* grandp = new_node->get_parent()->get_parent();

    parent->set_color(NodeRBTColor::BLACK);
    uncle->set_color(NodeRBTColor::BLACK);
    grandp->set_color(NodeRBTColor::RED);

    return grandp;
}

void RBT::RBT_Insert_PRed_UBlack(NodeRBT* new_node) {
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    if(parent == grandp->get_left())
    {
        if(new_node == parent->get_left()) { // ramo tutto a sx
            RBT_Insert_PRed_UBlack_LL(new_node);
        } else {
            RBT_LeftRotate(parent);
            RBT_Insert_PRed_UBlack_LL(parent);
        }
    } else {
        if(new_node == parent->get_right())
        {
            RBT_Insert_PRed_UBlack_RR(new_node);
        } else {
            RBT_RightRotate(parent);
            RBT_Insert_PRed_UBlack_RR(parent);
        }
    }
}

void RBT::RBT_RightRotate(NodeRBT* x) {

    NodeRBT* y = x->get_left();
    NodeRBT* z = y->get_right();
    NodeRBT* p = x->get_parent();

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

void RBT::RBT_LeftRotate(NodeRBT* x) { //y = parent x = grandparent z = newnode

    NodeRBT *y = x->get_right();
    NodeRBT *z = y->get_left();
    NodeRBT *p = x->get_parent();

    x->set_right(z);

    if(z != NULL)
    {
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

void RBT::RBT_Insert_PRed_UBlack_LL(NodeRBT* new_node) {
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    RBT_SwapColors(grandp, parent);
    RBT_RightRotate(grandp);
}

void RBT::RBT_Insert_PRed_UBlack_RR(NodeRBT* new_node) {
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    RBT_SwapColors(grandp, parent);
    RBT_LeftRotate(grandp);
}

void RBT::RBT_SwapColors(NodeRBT* node1, NodeRBT* node2) {
    NodeRBTColor temp = node1->get_color();
    node1->set_color(node2->get_color());
    node2->set_color(temp);
}

NodeRBT* RBT::RBT_Find(int key) {
    NodeRBT* ndpoint = get_root();

    while((ndpoint != nullptr)) {
        int currkey = ndpoint->get_key();
        if(currkey == key) {
            return ndpoint;
        }
        
        if(key < currkey)
            ndpoint = ndpoint->get_left();
        else
            ndpoint = ndpoint->get_right();
    }

    return nullptr;
}

void RBT::RBT_Clear(NodeRBT* x) {
    if(x == nullptr) {
        set_root(x);
        return;
    }
    
    RBT_Clear(x->get_right());
    RBT_Clear(x->get_left());
    
    delete x;
    x = nullptr;
    return;
}


void RBT::print_info(NodeRBT* x)
{
    if (x != nullptr){
        std::cout << "Nodo = " << x->get_key();
        if (x->get_color() == NodeRBTColor::BLACK){
            std::cout << "\nColor =  BLACK";
        } else{
            std::cout << "\nColor = RED";
        } 
        std::cout << "\nParent = ";
        if (x->get_parent() != nullptr){
        std::cout << x->get_parent()->get_key();
        } else {
            std::cout << "NULL";
        }
        std::cout << "\nLeft = ";
        if (x->get_left() != nullptr){
            std::cout << x->get_left()->get_key();
        } else {
            std::cout << "NULL";
        }
        std::cout << "\nRight = ";
        if (x->get_right() != nullptr){
            std::cout << x->get_right()->get_key();
        } else {
            std::cout << "NULL";
        }
        std::cout << "\n__________________\n\n";
        print_info(x->get_left());
        print_info(x->get_right());
    }
}