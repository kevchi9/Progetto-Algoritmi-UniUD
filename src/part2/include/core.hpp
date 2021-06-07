#ifndef _CORE_H
#define _CORE_H

#include <vector>
#include <string>

void generate_random_nodes(unsigned int n);

void core(char tree_type);

std::string rand_str_generator(const unsigned int length);

double calculate_mean(double times[], int find_times[]);

double calculate_stderr(double mean, double time_results[]);

void tree_tester(std::ofstream &output_file, int find_times[], double time_results[], double min, double max, char tree_type);

#endif