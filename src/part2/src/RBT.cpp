#include "../include/RBT.hpp"
#include "assert.h"
#include <iostream>

RBT::RBT(): root(nullptr) {}

void RBT::set_root(NodeRBT* x) 
{
    root = x;
    root->set_color(BLACK);
    assert(root->get_color() == BLACK);
}

NodeRBT* RBT::get_root() 
{
    return root;
}

void RBT::show(NodeRBT *x)
{
    if (x == nullptr)
    {
        std::cout << "NULL" << ' ';
        return;
    } 
    else 
    {
        std::cout << x->get_key() << ":" << x->get_value() << ":" << (x->get_color() == RED ? "red" : "black") << ' ';
    }
    
    show(x->get_left());
    show(x->get_right());
}

void RBT::insert(NodeRBT* new_node)
{    
    if(get_root() == nullptr) 
    {
        set_root(new_node);
        return;
    }

    NodeRBT* upper = nullptr;
    NodeRBT* lower = get_root();

    while(lower != nullptr) 
    {
        upper = lower;
        if (new_node->get_key() < lower->get_key())
        {
            lower = lower->get_left();
        }
        else 
        {
            lower = lower->get_right();
        }
    }

    new_node->set_color(RED);
    new_node->set_parent(upper);

    if (new_node->get_key() < upper->get_key())
    {
        upper->set_left(new_node);
    } 
    else 
    { 
        upper->set_right(new_node);
    }
    insert_fix(new_node);
}

void RBT::insert_fix(NodeRBT* new_node) 
{

    if(new_node->get_parent() == nullptr) 
    {
        new_node->set_color(BLACK);
        return;
    } 
    
    else if(new_node->get_parent()->get_color() == BLACK)
    {
        return;
    }

    else if((new_node->is_red_child_red()) && (new_node->get_uncle() == nullptr ? false : (new_node->get_uncle()->get_color() == RED))) // padre e zio rosso
    {
        NodeRBT* next_node = insert_PRed_URed(new_node);
        return insert_fix(next_node);
    }
    else if((new_node->is_red_child_red()) && (new_node->get_uncle() == nullptr ? true : (new_node->get_uncle()->get_color() == BLACK))) // padre rosso e zio nero
    {
        insert_PRed_UBlack(new_node);
    }
}
 
NodeRBT* RBT::insert_PRed_URed(NodeRBT* new_node) 
{
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* uncle = new_node->get_uncle();
    NodeRBT* grandp = new_node->get_parent()->get_parent();

    parent->set_color(BLACK);
    uncle->set_color(BLACK);
    grandp->set_color(RED);

    return grandp;
}

void RBT::insert_PRed_UBlack(NodeRBT* new_node) 
{
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    if(parent == grandp->get_left())
    {
        if(new_node == parent->get_left()) 
        { // ramo tutto a sx
            insert_PRed_UBlack_LL(new_node);
        } 
        else 
        {
            left_rot(parent);
            insert_PRed_UBlack_LL(parent);
        }
    } 
    else 
    {
        if(new_node == parent->get_right())
        {
            insert_PRed_UBlack_RR(new_node);
        } 
        else 
        {
            right_rot(parent);
            insert_PRed_UBlack_RR(parent);
        }
    }
}

void RBT::right_rot(NodeRBT* x) 
{

    NodeRBT* y = x->get_left();
    NodeRBT* z = y->get_right();
    NodeRBT* p = x->get_parent();

    x->set_left(z);
    if(z != NULL)
    {
        z->set_parent(x);
    }

    y->set_right(x);
    x->set_parent(y);

    if (x == get_root())
    {
        assert(p == NULL);
        set_root(y);
    } 
    else 
    {
        if(x == p->get_right())
        {
            p->set_right(y); 
        } 
        else 
        {
            p->set_left(y);
        }
    }
    y->set_parent(p);
}

void RBT::left_rot(NodeRBT* x) 
{ //y = parent x = grandparent z = newnode
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

    if (x == get_root())
    {
        assert(p == NULL);
        set_root(y);
    } 
    else 
    {
        if(x == p->get_left())
        {
            p->set_left(y); 
        } 
        else 
        {
            p->set_right(y);
        }
    }
    y->set_parent(p);
}

void RBT::insert_PRed_UBlack_LL(NodeRBT* new_node) 
{
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    swap_colors(grandp, parent);
    right_rot(grandp);
}

void RBT::insert_PRed_UBlack_RR(NodeRBT* new_node) 
{
    NodeRBT* parent = new_node->get_parent();
    NodeRBT* grandp = parent->get_parent();

    swap_colors(grandp, parent);
    left_rot(grandp);
}

void RBT::swap_colors(NodeRBT* node1, NodeRBT* node2) 
{
    node_color temp = node1->get_color();
    node1->set_color(node2->get_color());
    node2->set_color(temp);
}

NodeRBT* RBT::find(int k) 
{
    NodeRBT* x = get_root();

    while(x->get_key() != k && x != nullptr)
    {
        if (x->get_key() > k)
        {
            x = x->get_left();
        } 
        else 
        {
            x = x->get_right();
        }
    }
    return x;
}

std::string RBT::find_value(int k)
{
    NodeRBT* x = get_root();
    while(x != nullptr)
    {
        if (k > x->get_key())
        {
            x = x->get_right();
        } 
        else if (k < x->get_key())
        {
            x = x->get_left();
        } 
        else 
        {
            return x->get_value();    
        }
    }
    return "NULL";
}

void RBT::clear(NodeRBT* x) 
{
    if(x == nullptr) 
    {
        set_root(x);
        return;
    }
    
    clear(x->get_right());
    clear(x->get_left());
    
    delete x;
    x = nullptr;
    return;
}


void RBT::print_info(NodeRBT* x)
{
    if (x != nullptr)
    {
        std::cout << "Nodo = " << x->get_key();
        if (x->get_color() == BLACK)
        {
            std::cout << "\nColor =  BLACK";
        } 
        else
        {
            std::cout << "\nColor = RED";
        } 
        std::cout << "\nParent = ";
        if (x->get_parent() != nullptr)
        {
        std::cout << x->get_parent()->get_key();
        } 
        else 
        {
            std::cout << "NULL";
        }
        std::cout << "\nLeft = ";
        if (x->get_left() != nullptr)
        {
            std::cout << x->get_left()->get_key();
        } 
        else 
        {
            std::cout << "NULL";
        }
        std::cout << "\nRight = ";
        if (x->get_right() != nullptr)
        {
            std::cout << x->get_right()->get_key();
        } 
        else 
        {
            std::cout << "NULL";
        }
        std::cout << "\n__________________\n\n";
        print_info(x->get_left());
        print_info(x->get_right());
    }
}