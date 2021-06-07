#include "../include/core.hpp"
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include "../include/RBT.hpp"

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

std::string rand_str_generator(const unsigned int length)
{
    const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string rand_str_generator;

    for (unsigned int i = 0; i < length; ++i)
    {
        rand_str_generator += CHARACTERS[distribution(generator)];
    }

    return rand_str_generator;
}

void generate_random_nodes(unsigned int k)
{
    for (unsigned int i = 0; i < k; i++) 
    {
        input_keys.push_back(std::rand()%1000000); // il % impone un limite superiore al valore massimo per gli interi generati come chiave dei nodi 
        input_values.push_back(rand_str_generator(std::rand()%25));
    }
}

void core(char tree_type)
{
    double min = 1000;
    double max = 0;
    double err_ass = 0;
    int find_times[100];
    double time_results[100]; // all execution times in milliseconds

    std::ofstream output_file;
    tree_tester(output_file, find_times ,time_results, min, max, tree_type);

    double mean = calculate_mean(time_results, find_times);
    double standard_err = calculate_stderr(mean, time_results);
    output_file << ",,," << mean << ',' << standard_err << '\n';
}

double calculate_mean(double times[], int find_times[])
{
    double mean = 0;
    for(int i = 0; i < 100; i++)
    {
        mean += times[i] / find_times[i];
    }
    return mean / 100;
}

double calculate_stderr(double mean, double time_results[])
{
    double standard_err = 0;

    for (int i = 0; i < 100; i++)
    {
        standard_err += pow(time_results[i] - mean, 2);
    }
    return sqrt(standard_err / 100);
}


void tree_tester(std::ofstream &output_file,int find_times[] ,double time_results[], double min, double max, char tree_type)
{
    switch (tree_type)
    {
    case 'B':
        output_file.open ("tempi_BST.csv");
        break;
    case 'A':
        output_file.open ("tempi_AVL.csv");
        break;
    case 'R':
        output_file.open ("tempi_RBT.csv");
        break;
    default:
        exit(0);
        break;
    }
    output_file << " N. Find , Execution time , Inserted nodes , Mean , Std Err" <<'\n' ;
    for(int unsigned cicles = 1; cicles <= 100; cicles++)
    {
        std::cout << "Inizio del ciclo: " << cicles << '\n';

        unsigned int n_local = n * cicles;
        find_times[cicles-1] = n_local;
        generate_random_nodes(n_local);
        unsigned int inserted_nodes_counter = 0;
        switch(tree_type)
        {
            case 'B': // BST-type 
            {
                BST T;

                high_resolution_clock::time_point t1 = high_resolution_clock::now(); // start chronometer

                for (unsigned int i = 0; i < n_local; i++) // search for nodes and insert them if they are not in the tree
                {
                    std::string value_of_node = T.find_value(input_keys[i]);

                    if (value_of_node == "NULL")
                    {
                        Node *new_node = new Node(input_keys[i], input_values[i]);
                        T.insert(new_node);
                        inserted_nodes_counter++;
                    }
                }

                high_resolution_clock::time_point t2 = high_resolution_clock::now(); // stop chronometer
                duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

                double value_registered = time_span.count();
                
                output_file << n_local << ',' << value_registered << ',' <<inserted_nodes_counter << '\n' ;

                std::cout << "Tempo di esecuzione: " << value_registered << '\n';
                std::cout << "Nodi inseriti: " << inserted_nodes_counter << "\n\n";

                time_results[cicles - 1] = value_registered;
                break;
            }
            case 'A' : // AVL-type
            {
                AVL T;

                high_resolution_clock::time_point t1 = high_resolution_clock::now();

                for (unsigned int i = 0; i < n_local; i++)
                {
                    std::string value_of_node = T.find_value(input_keys[i]);

                    if (value_of_node == "NULL")
                    {
                        Node *new_node = new Node(input_keys[i], input_values[i]);
                        T.insert(new_node);
                        inserted_nodes_counter++;
                    }
                }

                high_resolution_clock::time_point t2 = high_resolution_clock::now();
                duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

                double value_registered = time_span.count();
                
                output_file << n_local << ',' << value_registered << ',' <<inserted_nodes_counter << '\n' ;

                std::cout << "Tempo di esecuzione: " << value_registered << '\n';
                std::cout << "Nodi inseriti: " << inserted_nodes_counter << "\n\n";

                time_results[cicles - 1] = value_registered;
                break;
            }
            case 'R' : // RBT-type
            {
                RBT T;

                high_resolution_clock::time_point t1 = high_resolution_clock::now();

                for (unsigned int i = 0; i < n_local; i++)
                {
                    std::string value_of_node = T.find_value(input_keys[i]);

                    if (value_of_node == "NULL")
                    {
                        NodeRBT *new_node = new NodeRBT(input_keys[i], input_values[i]);
                        T.insert(new_node);
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
                break;
            }
        }

        input_keys.clear();
        input_values.clear();
    }
}

/*
if(value_registered > max)
                {
                    max = value_registered;
                }
                else if (value_registered < min) 
                {
                    min = value_registered;
                }
*/