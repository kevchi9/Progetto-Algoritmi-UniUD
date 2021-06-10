#ifndef _CORE_H
#define _CORE_H

#include <vector>
#include <string>

void core();

void tree_tester(int find_times[]);

/**
 * Generates k nodes with a random key and a random value.
 */
void generate_random_nodes(unsigned int n);

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
double calculate_mean(double times_results[], int find_times[]);

/**
 * Calculates standard error of the find operation.
 * @param mean Mean of the find operations.
 * @param time_results The array containing the time measurements for n find operations.
 * @return The standard error.
 */
double calculate_stderr(double mean, double time_results[]);

#endif