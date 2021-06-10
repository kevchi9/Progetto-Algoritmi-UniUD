#ifndef _CORE_H
#define _CORE_H

#include <vector>
#include <string>

void generate_random_nodes(unsigned int n);

void core();

std::string rand_str_generator(const unsigned int length);

double calculate_mean(double times[], int find_times[]);

double calculate_stderr(double mean, double time_results[]);

void tree_tester(int find_times[]);

#endif