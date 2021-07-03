#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <assert.h>

AVL::AVL() : root(nullptr) {}

Node *AVL::get_root()
{
    return root;
}

void AVL::set_root(Node *x)
{
    root = x;
}

void AVL::show(Node *x)
{
    if (x == nullptr)
    {
        std::cout << "NULL" << ' ';
        return;
    }
    else
    {
        std::cout << x->get_key() << ':' << x->get_value() << ':' << x->get_height() << ' ';
    }
    show(x->get_left());
    show(x->get_right());
}

int AVL::get_balance(Node *x)
{
    if (x != nullptr)
    {
        if (x->get_left() == nullptr && x->get_right() != nullptr)
        {
            return -(x->get_right()->get_height());
        }
        else if (x->get_left() != nullptr && x->get_right() == nullptr)
        {
            return x->get_left()->get_height();
        }
        else
        {
            return (x->get_left()->get_height() - x->get_right()->get_height());
        }
    }
    else
    {
        return 0;
    }
}

void AVL::check_height(Node *x)
{
    std::cout << x->get_height() << '\n';
}

void AVL::fix_height(Node *x)
{
    Node *z = x->get_left();
    Node *y = x->get_right();

    if (z != nullptr && y != nullptr)
    {
        x->set_height(std::max(z->get_height(), y->get_height()) + 1);
    }
    else if (z != nullptr)
    {
        x->set_height(z->get_height() + 1);
    }
    else if (y != nullptr)
    {
        x->set_height(y->get_height() + 1);
    }
    else
    {
        x->set_height(1);
    }
}

void AVL::left_rot(Node *x)
{
    Node *y = x->get_right();
    Node *z = y->get_left();
    Node *p = x->get_parent();

    x->set_right(z);
    if (z != NULL)
    {
        z->set_parent(x);
    }

    y->set_left(x);
    x->set_parent(y);

    if (x == get_root())
    {
        // assert(p == NULL);
        set_root(y);
    }
    else
    {
        if (x == p->get_left())
        {
            p->set_left(y);
        }
        else
        {
            p->set_right(y);
        }
    }
    y->set_parent(p);

    fix_height(x);
    fix_height(y);
    Node *w = y->get_parent();
    while (w != nullptr)
    {
        fix_height(w);
        w = w->get_parent();
    }
}

void AVL::right_rot(Node *x)
{
    Node *y = x->get_left();
    Node *z = y->get_right();
    Node *p = x->get_parent();

    x->set_left(z);
    if (z != NULL)
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
        if (x == p->get_right())
        {
            p->set_right(y);
        }
        else
        {
            p->set_left(y);
        }
    }
    y->set_parent(p);

    fix_height(x);
    fix_height(y);
    Node *w = y->get_parent();
    while (w != nullptr)
    {
        fix_height(w);
        w = w->get_parent();
    }
}

void AVL::right_left_rot(Node *x)
{
    Node *y = x->get_right();
    assert(y != NULL);
    Node *z = y->get_left();
    assert(z != NULL);

    right_rot(y);
    left_rot(x);
}

void AVL::left_right_rot(Node *x)
{
    Node *y = x->get_left();
    assert(y != NULL);
    Node *z = y->get_right();
    assert(z != NULL);

    left_rot(y);
    right_rot(x);
}

Node *AVL::find(int k)
{
    Node *x = get_root();

    while (x->get_key() != k && x != nullptr)
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

std::string AVL::find_value(int k)
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

void AVL::transplant(Node *u, Node *v)
{
    if (u == get_root())
    {
        if (v != nullptr)
        {
            v->set_parent(u->get_parent());
        }
        set_root(v);
        return;
    }
    else if (u == u->get_parent()->get_left())
    { // se u è figlio sx
        u->get_parent()->set_left(v);
    }
    else
    {
        u->get_parent()->set_right(v);
    }
    if (v != nullptr)
    {
        v->set_parent(u->get_parent());
    }
    u->set_parent(nullptr);
}
/*
void AVL::remove(int k)
{
    Node *z = find(k);
    Node *p = z->get_parent();
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
        Node *y = minimum(z->get_right()); // cerco il successore
        if (y->get_parent() != z)
        { // il minimo non è direttamente collegato a z
            transplant(y, y->get_right());
            y->set_right(z->get_right());
            if (y->get_right() != nullptr)
            {
                y->get_right()->set_parent(y);
            }
        }

        transplant(z, y);
        y->set_left(z->get_left());
        y->get_left()->set_parent(y);
    }
    delete z;
    if (p != nullptr)
    {
        balance_helper(p);
    }
}
*/

void AVL::insert(Node *x)
{
    insert_helper(get_root(), nullptr, x);
}

void AVL::insert_helper(Node *x, Node *p, Node *y)
{
    insert_and_balance(x, p, y);
    balance_helper(y->get_parent());
}

int AVL::insert_and_balance(Node *x, Node *p, Node *y)
{
    int k = y->get_key();
    if (get_root() == nullptr) // if tree was empty
    {
        set_root(y);
        return y->get_height();
    }

    if (x == nullptr)
    {
        y->set_parent(p);

        if (k < p->get_key())
        {
            p->set_left(y);
        }
        else
        {
            p->set_right(y);
        }
        return y->get_height();
    }
    else if (k < x->get_key())
    {
        Node *l = x->get_left();

        if (x->get_height() < insert_and_balance(l, x, y) + 1)
        {
            x->increase_height();
            return x->get_height();
        }
    }
    else
    {
        Node *r = x->get_right();

        if (x->get_height() < insert_and_balance(r, x, y) + 1)
        {
            x->increase_height();
            return x->get_height();
        }
    }
    return 0;
}

void AVL::balance_helper(Node *x) // anticamera del balance
{
    if (x != nullptr)
    {
        Node *p = x->get_parent();

        if (get_balance(x) < -1 || get_balance(x) > 1)
        {
            balance(x);
        }
        balance_helper(p);
    }
}

void AVL::balance(Node *x)
{
    Node *left = x->get_left();
    Node *right = x->get_right();
    if (get_balance(x) > 1) // sbilanciato a sx
    {
        if (get_balance(left) == 1) // rotations on left subtree
        {
            right_rot(x);
        }
        else
        {
            left_right_rot(x);
        }
    }
    else if (get_balance(x) < -1) // sbilanciato a dx
    {
        if (get_balance(right) == -1) // rotations on right subtree
        {
            left_rot(x);
        }
        else
        {
            right_left_rot(x);
        }
    }
}

void AVL::clear(Node *x)
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
