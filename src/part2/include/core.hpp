#ifndef _CORE_H
#define _CORE_H

#include "Node.hpp"
#include <vector>
#include <chrono>
#include <string>
#include <array>
#include <cmath>

constexpr int n_find = 100;
constexpr int n = 500;
constexpr int n_cicles = 100;

void core();

void tree_tester(std::array<int, n_find> &numero_find);

/**
 * Generates k nodes with a random key and a random value.
 */
std::pair<std::vector<int>, std::vector<std::string>> generate_random_nodes(unsigned int n);

std::pair<std::vector<int>, std::vector<std::string>> generate_random_nodes_worst_case(unsigned int n);

/**
 * Function used for Nodes' random values.
 */
std::string rand_str_generator(const unsigned int length);

/**
 * Calculates mean of the find operations.
 * @param times_results The array containing the time measurements for n find operations.
 * @param find_times The array containing the number of find operation for each cicle.
 * @return The mean.
 */
template <std::size_t L>
double calculate_mean(std::array<double, L> &times, std::array<int, L> &numero_find)
{
    double mean = 0;
    unsigned int counter = 0;
    for (const auto &i : numero_find)
    {
        mean += times[counter] / i;
        counter++;
    }
    return mean / 100;
}

/**
 * Calculates standard error of the find operation.
 * @param mean Mean of the find operations.
 * @param time_results The array containing the time measurements for n find operations.
 * @return The standard error.
 */
template <std::size_t L>
double calculate_stderr(double mean, std::array<double, L> &time_results)
{
    double standard_err = 0;

    for (const auto &i : time_results)
    {
        standard_err += pow(i - mean, 2);
    }
    // auto pow_lambda = [mean](const auto &val)
    // {
    //     return pow(val - mean, 2);
    // };

    // standard_err = std::accumulate(time_results.begin(), time_results.end(), 0, pow_lambda);

    return sqrt(standard_err / 100);
}

#endif