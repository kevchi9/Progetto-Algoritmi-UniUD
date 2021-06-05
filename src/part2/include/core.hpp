#ifndef _CORE_H
#define _CORE_H

#include <vector>

void generate_random_nodes(unsigned int n);

void main_BST();

std::string random_string(unsigned int length);

double calculate_mean(double times[]);

double calculate_stderr(double mean, double time_results[]);

void tree_tester(std::ofstream &output_file, double time_results[], double min, double max);

#endif