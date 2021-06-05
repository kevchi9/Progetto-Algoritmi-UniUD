#include "../include/core.hpp"
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"

#include <chrono>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std::chrono;

std::vector<int> input_keys;

std::vector<std::string> input_values;

int n = 1000;

std::string random_string(unsigned int length)
{
    const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (unsigned int i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

void generate_random_nodes(unsigned int k){
    
    
    for (unsigned int i = 0; i < k; i++) {
        input_keys.push_back(std::rand()%1000000); // il % impone un limite superiore al valore massimo per gli interi generati come chiave dei nodi 
        input_values.push_back(random_string(std::rand()%25));
    }
}

void main_BST()
{
    double min = 1000;
    double max = 0;
    double err_ass = 0;
    double time_results[100];

    std::ofstream output_file;
    output_file.open ("tempi.csv");

    tree_tester(output_file, time_results, min, max);

    double mean = calculate_mean(time_results);

    double standard_err = calculate_stderr(mean, time_results);

    
}

double calculate_stderr(double mean, double time_results[])
{
    double standard_err = 0;

    for (int i = 0; i < 100; i++)
    {
        standard_err += pow(time_results[i] - mean, 2);
    }

    standard_err = standard_err / 100;

    return sqrt(standard_err);
}

double calculate_mean(double times[])
{
    double mean = 0;

    for(int i = 0; i < 100; i++)
    {
        mean += times[i];
    }

    return mean / 100;
}

void tree_tester(std::ofstream &output_file, double time_results[], double min, double max)
{

    for(int unsigned cicles = 1; cicles <= 100; cicles++)
    {
        std::cout << "Inizio del ciclo: " << cicles << '\n';

        unsigned int n_local = n * cicles;
        generate_random_nodes(n_local);
        unsigned int inserted_nodes_counter = 0;
        BST T;

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        for (unsigned int i = 0; i < n_local; i++)
        {
            std::string value_of_node = T.find_value(input_keys[i]);

            if (value_of_node == "NULL")
            {
                Node *new_node = new Node(input_keys[i], input_values[i]);
                T.BST_insert(new_node);
                inserted_nodes_counter++;
            }
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

        double value_registered = time_span.count();
        
        output_file << n_local << ',' << value_registered << '\n' ;

        std::cout << "Tempo di esecuzione: " << value_registered << '\n';
        std::cout << "Nodi inseriti: " << inserted_nodes_counter << "\n\n";

        time_results[cicles - 1] = value_registered;

        if(value_registered > max)
        {
            max = value_registered;
        }
        else if (value_registered < min) 
        {
            min = value_registered;
        }

        input_keys.clear();
        input_values.clear();
    }
}
