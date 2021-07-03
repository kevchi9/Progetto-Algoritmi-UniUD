#ifndef _COMMON_H
#define _COMMON_H

#include "Node.hpp"
#include "NodeRBT.hpp"
#include "core.hpp"

#include <vector>
#include <chrono>
#include <string>
#include <array>
#include <cmath>

double get_system_resolution();

template <typename N>
void clear_tree(N *x)
{
    if (x == nullptr)
    {
        return;
    }
    clear_tree(x->get_left());
    clear_tree(x->get_right());
    delete x;
    return;
}

std::pair<std::vector<int>, std::vector<std::string>> generate_random(unsigned int k);

std::pair<std::vector<int>, std::vector<std::string>> generate_random_worst(unsigned int k);

#endif