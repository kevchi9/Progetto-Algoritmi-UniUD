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
using t_precision = std::chrono::nanoseconds;
std::vector<int> input_keys;

std::vector<std::string> input_values;

int n = 500;

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
        input_keys.push_back(std::rand() % 50000); // il % impone un limite superiore al valore massimo per gli interi generati come chiave dei nodi
        input_values.push_back(rand_str_generator(std::rand() % 25));
    }
}

void generate_random_nodes_worst_case(unsigned int k)
{
    for (unsigned int i = 1; i < k; i++)
    {
        input_keys.push_back(i);
        input_values.push_back(rand_str_generator(std::rand() % 25));
    }
}

void core()
{
    int numero_find[100];

    tree_tester(numero_find);
}

double calculate_mean(double times[], int numero_find[])
{
    double mean = 0;
    for (int i = 0; i < 100; i++)
    {
        mean += times[i] / numero_find[i];
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


void tree_tester(int numero_find[])
{
    const unsigned int n_cicles = 100;
    std::ofstream output_file1;
    std::ofstream output_file2;
    std::ofstream output_file3;

    // inizializzazione e formattazione dei file
    output_file1.open("tempi_BST.csv");
    output_file2.open("tempi_AVL.csv");
    output_file3.open("tempi_RBT.csv");

    output_file1 << " N.Find , Find_ops_time_exec , N.Insert , Insert_ops_time_exec , Total_execution_time , Find_mean , Std_Err " << '\n';
    output_file1.flush();
    output_file2 << " N.Find , Find_ops_time_exec , N.Insert , Insert_ops_time_exec , Total_execution_time , Find_mean , Std_Err " << '\n';
    output_file2.flush();
    output_file3 << " N.Find , Find_ops_time_exec , N.Insert , Insert_ops_time_exec , Total_execution_time , Find_mean , Std_Err " << '\n';
    output_file3.flush();

    double BST_time_results[n_cicles];
    double AVL_time_results[n_cicles];
    double RBT_time_results[n_cicles];

    unsigned int inserted_nodes_counter = 0;

    for (int unsigned cicles = 1; cicles <= n_cicles; cicles++)
    {
        std::cout << "Completato al " << cicles << "% \n";

        unsigned int n_nodi = n * cicles;
        // numero_find[cicles - 1] = n_nodi;

        generate_random_nodes_worst_case(n_nodi);

        // inizio esecuzione BST

        BST BST_tree;

        double BST_sum_find_time = 0;
        double BST_sum_insert_time = 0;

        for (unsigned int i = 0; i < n_nodi; i++) // search for nodes and insert them if they are not in the tree
        {   
            auto BST_t1_find = steady_clock::now(); // start find chronometer
            std::string value_of_node = BST_tree.find_value(input_keys[i]);
            auto BST_t2_find = steady_clock::now(); // stop find chronometer

            BST_sum_find_time += duration_cast<t_precision>(BST_t2_find - BST_t1_find).count()  ;

            if (value_of_node == "NULL")
            {
                Node *new_node = new Node(input_keys[i], input_values[i]);

                auto BST_t1_insert = steady_clock::now(); // start insert chronometer
                BST_tree.insert(new_node);
                auto BST_t2_insert = steady_clock::now(); // stop insert chronometer

                inserted_nodes_counter++;

                BST_sum_insert_time += duration_cast<t_precision>(BST_t2_insert - BST_t1_insert).count();
            }

        }   
        BST_tree.clear(BST_tree.get_root());

        double mean = BST_sum_find_time/n_nodi;
        double total_time = BST_sum_find_time + BST_sum_insert_time;

        output_file1 << n_nodi << ',' << BST_sum_find_time << ',' << inserted_nodes_counter << ','<< BST_sum_insert_time << ',' << total_time << ',' << mean <<'\n';
        output_file1.flush();

        BST_time_results[cicles - 1] = total_time;
        inserted_nodes_counter = 0;

        // fine esecuzione BST - inizio esecuzione AVL

        AVL AVL_tree;

        double AVL_sum_find_time = 0;
        double AVL_sum_insert_time = 0;

        for (unsigned int i = 0; i < n_nodi; i++)
        {
            auto AVL_t1_find = steady_clock::now();
            std::string AVL_value_of_node = AVL_tree.find_value(input_keys[i]);
            auto AVL_t2_find = steady_clock::now();

            AVL_sum_find_time += duration_cast<t_precision>(AVL_t2_find - AVL_t1_find).count();

            if (AVL_value_of_node == "NULL")
            {
                Node *new_node = new Node(input_keys[i], input_values[i]);

                auto AVL_t1_insert = steady_clock::now();
                AVL_tree.insert(AVL_tree.get_root(), nullptr, new_node);
                auto AVL_t2_insert = steady_clock::now();

                inserted_nodes_counter++;

                AVL_sum_insert_time += duration_cast<t_precision>(AVL_t2_insert - AVL_t1_insert).count();
            }
        }
        AVL_tree.clear(AVL_tree.get_root());

        mean = AVL_sum_find_time/n_nodi;
        total_time = AVL_sum_find_time + AVL_sum_insert_time;

        output_file2 << n_nodi << ',' << AVL_sum_find_time << ',' << inserted_nodes_counter << ','<< AVL_sum_insert_time << ',' << total_time << ',' << mean <<'\n';
        output_file2.flush();

        AVL_time_results[cicles - 1] = total_time;
        inserted_nodes_counter = 0;

        // fine esecuzione AVL - inizio esecuzione RBT

        RBT RBT_tree;

        double RBT_sum_find_time = 0;
        double RBT_sum_insert_time = 0;

        for (unsigned int i = 0; i < n_nodi; i++)
        {
            auto RBT_t1_find = steady_clock::now();
            std::string RBT_value_of_node = RBT_tree.find_value(input_keys[i]);
            auto RBT_t2_find = steady_clock::now();

            RBT_sum_find_time += duration_cast<t_precision>(RBT_t2_find - RBT_t1_find).count();

            if (RBT_value_of_node == "NULL")
            {
                NodeRBT *new_node = new NodeRBT(input_keys[i], input_values[i]);

                auto RBT_t1_insert = steady_clock::now();
                RBT_tree.insert(new_node);
                auto RBT_t2_insert = steady_clock::now();

                inserted_nodes_counter++;

                RBT_sum_insert_time += duration_cast<t_precision>(RBT_t2_insert - RBT_t1_insert).count();
            }
        }
        RBT_tree.clear(RBT_tree.get_root());

        mean = RBT_sum_find_time/n_nodi;
        total_time = RBT_sum_find_time + AVL_sum_insert_time;

        output_file3 << n_nodi << ',' << RBT_sum_find_time << ',' << inserted_nodes_counter << ','<< RBT_sum_insert_time << ',' << total_time << ',' << mean <<'\n';
        output_file3.flush();

        RBT_time_results[cicles - 1] = total_time;
        inserted_nodes_counter = 0;

        std::cout << "BST_find_time - AVL_find_time = " << BST_sum_find_time - AVL_sum_find_time << '\n';

        input_keys.clear();
        input_values.clear();
        // fine esecuzione RBT 

    } // fine 100 cicli


    // calcolo medie e stderr dei tre alberi
    double BST_mean = calculate_mean(BST_time_results, numero_find);
    double AVL_mean = calculate_mean(AVL_time_results, numero_find);
    double RBT_mean = calculate_mean(RBT_time_results, numero_find);

    double BST_stderr = calculate_stderr(BST_mean, BST_time_results);
    double ALV_stderr = calculate_stderr(AVL_mean, AVL_time_results);
    double RBT_stderr = calculate_stderr(RBT_mean, RBT_time_results);

    output_file1 << ",,,,," << BST_mean << ',' << BST_stderr << '\n';
    output_file1.flush();
    output_file2 << ",,,,," << AVL_mean << ',' << ALV_stderr << '\n';
    output_file2.flush();
    output_file3 << ",,,,," << RBT_mean << ',' << RBT_stderr << '\n';
    output_file3.flush();

    // chiusura dei 3 file

    output_file1.close();
    output_file2.close();
    output_file3.close();
}