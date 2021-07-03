#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include "../include/RBT.hpp"
#include "../include/core.hpp"
#include "../include/common.hpp"

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cmath>
#include <array>
#include <fstream>
#include <algorithm>
#include <numeric>

using t_precision = std::chrono::nanoseconds;

constexpr int a{1000};
int iter{100};
constexpr double max_error{0.01};
const auto resolution{get_system_resolution()};
const int t_min{static_cast<int>(resolution * ((1 / max_error) + 1))};
constexpr int iter_var{20};

void progress_bar(int iterazione, int max_iterazione, int n_nodi, int &step)
{
    int percentuale = (100 * (iterazione + 1)) / iter;

    if (percentuale >= step)
    {
        std::cout << '\r' << percentuale << "% [" << std::string(percentuale / 3, '=') << '>' << std::string((100 / 3 - percentuale / 3) - 1, ' ') << ']';
        std::cout << "[Iterazione " << iterazione + 1 << " / " << max_iterazione << "] - numero di nodi: " << n_nodi;
        std::cout.flush();
        ++step;
    }
}

template <typename T, typename N>
void test_with_nodes(std::pair<std::vector<int>, std::vector<std::string>> &keys, std::ofstream &output_file, int n_of_nodes)
{
    std::vector<N *> nodes;
    nodes.reserve(n_of_nodes);
    for (int i = 0; i < n_of_nodes; ++i)
    {
        nodes.push_back(new N(keys.first[i], keys.second[i]));
    }

    int c = 0;
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point t2;

    do
    {
        T tree;

        for (const auto &node : nodes)
        {
            if (tree.find_value(node->get_key()) == "NULL")
            {
                tree.insert(node);
            }
        }

        t2 = std::chrono::steady_clock::now();
        ++c;
        tree.clear(tree.get_root());

    } while (t_min > std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

    double tempo_iterazione = static_cast<double>(std::chrono::duration_cast<t_precision>(t2 - t1).count()) / c;
    double tempo_ammortizzato = tempo_iterazione / n_of_nodes;

    output_file << n_of_nodes << ',' << tempo_ammortizzato << '\n';
    output_file.flush();
}

template <typename T, typename N>
void varianza(std::pair<std::vector<int>, std::vector<std::string>> &keys, std::ofstream &output_file, int n_of_nodes)
{
    double varianza{0.0};
    double tempo_medio{0.0};
    std::array<double, iter_var> tempi;

    for (int i = 0; i < iter_var; ++i)
    {
        std::vector<N *> nodes;
        nodes.reserve(n_of_nodes);
        for (int j = 0; j < n_of_nodes; ++j)
        {
            nodes.push_back(new N(keys.first[j], keys.second[j]));
        }

        std::cout << "Varianza: " << i << '/' << iter_var << '\n';
        int c = 0;
        auto t1 = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point t2;

        do
        {
            T tree;

            for (const auto &node : nodes)
            {
                if (tree.find_value(node->get_key()) == "NULL")
                {
                    tree.insert(node);
                }
            }

            t2 = std::chrono::steady_clock::now();
            ++c;
            // clear_tree<N>(tree.get_root());
            tree.clear(tree.get_root());
        } while (t_min > std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

        double tempo_iterazione = (static_cast<double>(std::chrono::duration_cast<t_precision>(t2 - t1).count()) / c) / n_of_nodes;
        tempi[i] = tempo_iterazione;
        tempo_medio += tempo_iterazione;
    }

    tempo_medio /= iter_var;

    // auto lambda_func = [&](double counter, const double tempo)
    // { return counter + pow(tempo - tempo_medio, 2); };
    // varianza = std::accumulate(tempi.begin(), tempi.end(), 0.0, lambda_func);

    for (const auto &tempo : tempi)
    {
        varianza += pow(tempo - tempo_medio, 2);
    }

    output_file << n_of_nodes << ',' << varianza << '\n';
    output_file.flush();
}

void test_tree(bool worst_case)
{
    std::ofstream output_file_bst;
    std::ofstream output_file_rbt;
    std::ofstream output_file_avl;

    if (worst_case)
    {
        output_file_bst.open("tempi_BST_worst.csv");
        output_file_rbt.open("tempi_RBT_worst.csv");
        output_file_avl.open("tempi_AVL_worst.csv");
    }
    else
    {
        output_file_bst.open("tempi_BST.csv");
        output_file_rbt.open("tempi_RBT.csv");
        output_file_avl.open("tempi_AVL.csv");
    }
    output_file_bst << "N, Tempo_Ammortizzato" << '\n';
    output_file_bst.flush();
    output_file_rbt << "N, Tempo_Ammortizzato" << '\n';
    output_file_rbt.flush();
    output_file_avl << "N, Tempo_Ammortizzato" << '\n';
    output_file_avl.flush();

    int displayNext = 1;
    for (int i = 0; i < iter; ++i)
    {
        int n_of_nodes{static_cast<int>(a * pow(1000, static_cast<double>(i) / 99))};
        progress_bar(i, iter, n_of_nodes, displayNext);

        std::pair<std::vector<int>, std::vector<std::string>> nodes;
        if (!worst_case)
        {
            nodes = generate_random(n_of_nodes);
        }
        else
        {
            nodes = generate_random_worst(n_of_nodes);
        }

        test_with_nodes<BST, Node>(nodes, output_file_bst, n_of_nodes);
        test_with_nodes<RBT, NodeRBT>(nodes, output_file_rbt, n_of_nodes);
        test_with_nodes<AVL, Node>(nodes, output_file_avl, n_of_nodes);
    }

    output_file_bst.close();
    output_file_rbt.close();
    output_file_avl.close();
}

void calc_varianza()
{
    std::ofstream output_file_bst;
    std::ofstream output_file_rbt;
    std::ofstream output_file_avl;
    output_file_bst.open("varianza_BST.csv");
    output_file_rbt.open("varianza_RBT.csv");
    output_file_avl.open("varianza_AVL.csv");

    output_file_bst << "N, Varianza" << '\n';
    output_file_bst.flush();
    output_file_rbt << "N, Varianza" << '\n';
    output_file_rbt.flush();
    output_file_avl << "N, Varianza" << '\n';
    output_file_avl.flush();

    int displayNext = 1;
    for (int i = 0; i < iter; ++i)
    {
        int n_of_nodes{static_cast<int>(a * pow(1000, static_cast<double>(i) / 99))};
        progress_bar(i, iter, n_of_nodes, displayNext);

        std::pair<std::vector<int>, std::vector<std::string>> nodes;

        nodes = generate_random(n_of_nodes);

        varianza<BST, Node>(nodes, output_file_bst, n_of_nodes);
        varianza<RBT, NodeRBT>(nodes, output_file_rbt, n_of_nodes);
        varianza<AVL, Node>(nodes, output_file_avl, n_of_nodes);
    }

    output_file_bst.close();
    output_file_rbt.close();
    output_file_avl.close();
}

void start_test(const bool worst_case)
{
    unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    std::srand(seed);

    test_tree(worst_case);
    if (!worst_case)
    {
        calc_varianza();
    }
}
