#include "../include/common.hpp"
#include <stdlib.h>
#include <chrono>

double get_system_resolution()
{
    auto start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;

    do
    {
        end = std::chrono::steady_clock::now();
    } while (start == end);

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

std::pair<std::vector<int>, std::vector<std::string>> generate_random(unsigned int k)
{
    std::vector<int> nodes;
    std::vector<std::string> strings;
    nodes.reserve(k);
    strings.reserve(k);

    for (unsigned int i = 0; i < k; ++i)
    {
        auto key = std::rand(); // il % impone un limite superiore al valore massimo per gli interi generati come chiave dei nodi
        auto value = rand_str_generator(std::rand() % 25);
        nodes.push_back(key);
        strings.push_back(value);
    }

    return std::make_pair(nodes, strings);
}

std::pair<std::vector<int>, std::vector<std::string>> generate_random_worst(unsigned int k)
{
    std::vector<int> nodes;
    std::vector<std::string> strings;
    nodes.reserve(k);
    strings.reserve(k);

    for (unsigned int key = 0; key < k; ++key)
    {
        auto value = rand_str_generator(std::rand() % 25);
        nodes.push_back(key);
        strings.push_back(value);
    }

    return std::make_pair(nodes, strings);
}