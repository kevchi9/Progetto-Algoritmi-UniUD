#include "../include/Node.hpp"
#include "../include/BST.hpp"
#include <iostream>
#include <assert.h>

// PER DEBUGGARE USA GLI ASSERT
// OGNI VOLTA CHE C'è UNA FRECCIA USA UN ASSERT
// OGNI FRECCETTA è UN POTENZIALE SEGFAULT

BST::BST() : root(nullptr) {}

Node *BST::get_root()
{
    return this->root;
}

void BST::set_root(Node *x)
{
    root = x;
}

void BST::show(Node *x)
{
    if (x == nullptr)
    {
        std::cout << "NULL" << ' ';
        return;
    }
    else
    {
        std::cout << x->get_key() << ':' << x->get_value() << ' ';
    }
    show(x->get_left());
    show(x->get_right());
    //std::cout << '\n';
}

void BST::insert(Node *z)
{
    Node *y = nullptr;
    Node *x = get_root();

    if (x == nullptr)
    { // if tree was empty
        set_root(z);
        return;
    }
    while (x != nullptr)
    {
        y = x;
        if (z->get_key() < x->get_key())
        {
            x = x->get_left();
        }
        else
        {
            x = x->get_right();
        }
    }
    z->set_parent(y);
    if (z->get_key() < y->get_key())
    {
        y->set_left(z);
    }
    else
    {
        y->set_right(z);
    }
}

void BST::transplant(Node *u, Node *v)
{
    std::cout << "rrrrrrrr\n";
    if (u == get_root())
    {
        std::cout << "aaaaaa1123234\n";
        set_root(v);
        return;
    }
    else if (u == u->get_parent()->get_left())
    { // se u è figlio sx
        u->get_parent()->set_left(v);
    }
    else
    {
        u->get_parent()->set_right(v); // se u è figlio dx
    }
    if (v != nullptr)
    {
        v->set_parent(u->get_parent());
    }
}

void BST::remove(int k)
{
    Node *z = find(k);

    if (z->get_left() == nullptr)
    { // il nodo da rimuovere non ha figlio sx
        transplant(z, z->get_right());
    }
    else if (z->get_right() == nullptr)
    { // non ha figlio dx
        transplant(z, z->get_left());
    }
    else
    {                                      // ha entrambi i figli
        Node *y = minimum(z->get_right()); // cerco il minimo

        if (y->get_parent() != z)
        { // il minimo non è direttamente collegato a z
            transplant(y, y->get_right());
            y->set_right(z->get_right());
            y->get_right()->set_parent(y);
        }
        if (z == get_root())
        {
            set_root(y);
        } // il minimo è figlio diretto di z
        transplant(z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);
    }
    delete z;
}

Node *BST::minimum(Node *x)
{
    while (x->get_left() != nullptr)
    {
        x = x->get_left();
    }
    return x;
}

Node *BST::find(int k)
{
    Node *x = get_root();
    while (x->get_key() != k)
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

std::string BST::find_value(int k)
{
    Node *x = get_root();
    while (x != nullptr)
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

void BST::clear(Node *x)
{

    if (x == nullptr)
    {
        set_root(x);
        return;
    }
    clear(x->get_left());
    clear(x->get_right());
    delete x;
}

void BST::print_info(Node *x)
{
    if (x != nullptr)
    {
        std::cout << "Nodo " << x->get_key();
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
        std::cout << "\n__________________\n";
        print_info(x->get_left());
        print_info(x->get_right());
    }
}