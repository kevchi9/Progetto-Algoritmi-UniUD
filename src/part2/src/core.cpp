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
        input_keys.push_back(std::rand() % 1000000); // il % impone un limite superiore al valore massimo per gli interi generati come chiave dei nodi
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
/*
    TODO: rivedi tree tester
    fai in modo che le sequenze di nodi generate dal primo for vengano usate in tutte le strutture (togli lo switch)
    praticamente fai un ciclo di BST poi uno di AVL e uno di RBT e così di nuovo fino alla fine del centesimo ciclo
*/

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

    output_file1 << " N. Find , Execution time , Inserted nodes , Mean , Std Err" << '\n';
    output_file1.flush();
    output_file2 << " N. Find , Execution time , Inserted nodes , Mean , Std Err" << '\n';
    output_file2.flush();
    output_file3 << " N. Find , Execution time , Inserted nodes , Mean , Std Err" << '\n';
    output_file3.flush();

    double BST_time_results[n_cicles];
    double AVL_time_results[n_cicles];
    double RBT_time_results[n_cicles];

    for (int unsigned cicles = 1; cicles <= n_cicles; cicles++)
    {
        std::cout << "Inizio del ciclo: " << cicles << '\n';

        unsigned int n_nodi = n * cicles;
        numero_find[cicles - 1] = n_nodi;

        generate_random_nodes(n_nodi);

        unsigned int inserted_nodes_counter = 0;

        // inizio esecuzione BST

        BST BST_tree;

        auto BST_t1 = steady_clock::now(); // start chronometer

        for (unsigned int i = 0; i < n_nodi; i++) // search for nodes and insert them if they are not in the tree
        {
            std::string value_of_node = BST_tree.find_value(input_keys[i]);

            if (value_of_node == "NULL")
            {
                Node *new_node = new Node(input_keys[i], input_values[i]);
                BST_tree.insert(new_node);
                inserted_nodes_counter++;
            }
        }

        auto BST_t2 = steady_clock::now(); // stop chronometer
        duration<double> BST_time_span = duration_cast<duration<double>>(BST_t2 - BST_t1);

        double value_registered = BST_time_span.count();

        output_file1 << n_nodi << ',' << value_registered << ',' << inserted_nodes_counter << '\n';
        output_file1.flush();

        std::cout << "Tempo di esecuzione BST: " << value_registered << '\n';
        std::cout << "Nodi inseriti in BST: " << inserted_nodes_counter << "\n\n";

        BST_time_results[cicles - 1] = value_registered;
        inserted_nodes_counter = 0;

        // fine esecuzione BST - inizio esecuzione AVL

        AVL AVL_tree;

        auto AVL_t1 = steady_clock::now();

        for (unsigned int i = 0; i < n_nodi; i++)
        {
            std::string value_of_node = AVL_tree.find_value(input_keys[i]);

            if (value_of_node == "NULL")
            {
                Node *new_node = new Node(input_keys[i], input_values[i]);
                AVL_tree.insert(AVL_tree.get_root(), nullptr, new_node);
                inserted_nodes_counter++;
            }
        }

        auto AVL_t2 = steady_clock::now();
        duration<double> AVL_time_span = duration_cast<duration<double>>(AVL_t2 - AVL_t1);

        double AVL_value_registered = AVL_time_span.count(); // il lasso temporale per l'esecuzione di un ciclo

        output_file2 << n_nodi << ',' << AVL_value_registered << ',' << inserted_nodes_counter << '\n';
        output_file2.flush();

        std::cout << "Tempo di esecuzione AVL: " << AVL_value_registered << '\n';
        std::cout << "Nodi inseriti in AVL: " << inserted_nodes_counter << "\n\n";
        AVL_time_results[cicles - 1] = value_registered;
        inserted_nodes_counter = 0;

        // fine esecuzione AVL - inizio esecuzione RBT

        RBT RBT_tree;

        auto RBT_t1 = steady_clock::now();

        for (unsigned int i = 0; i < n_nodi; i++)
        {
            std::string value_of_node = RBT_tree.find_value(input_keys[i]);

            if (value_of_node == "NULL")
            {
                NodeRBT *new_node = new NodeRBT(input_keys[i], input_values[i]);
                RBT_tree.insert(new_node);
                inserted_nodes_counter++;
            }
        }

        auto RBT_t2 = steady_clock::now();
        duration<double> RBT_time_span = duration_cast<duration<double>>(RBT_t2 - RBT_t1);

        double RBT_value_registered = RBT_time_span.count();

        output_file3 << n_nodi << ',' << RBT_value_registered << ',' << inserted_nodes_counter << '\n';
        output_file3.flush();

        std::cout << "Tempo di esecuzione RBT: " << RBT_value_registered << '\n';
        std::cout << "Nodi inseriti in RBT: " << inserted_nodes_counter << "\n\n";

        RBT_time_results[cicles - 1] = RBT_value_registered;
        inserted_nodes_counter = 0;


        // fine esecuzione RBT 

    } // fine 100 cicli


    // calcolo medie e stderr dei tre alberi
    double BST_mean = calculate_mean(BST_time_results, numero_find);
    double AVL_mean = calculate_mean(AVL_time_results, numero_find);
    double RBT_mean = calculate_mean(RBT_time_results, numero_find);

    output_file1 << ",,," << BST_mean << ',' << calculate_stderr(BST_mean, BST_time_results) << '\n';
    output_file1.flush();
    output_file2 << ",,," << AVL_mean << ',' << calculate_stderr(AVL_mean, AVL_time_results) << '\n';
    output_file2.flush();
    output_file3 << ",,," << RBT_mean << ',' << calculate_stderr(RBT_mean, RBT_time_results) << '\n';
    output_file3.flush();

    // chiusura dei 3 file

    output_file1.close();
    output_file2.close();
    output_file3.close();
}