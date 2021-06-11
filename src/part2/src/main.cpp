#include "../include/core.hpp"
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include "../include/RBT.hpp"
#include "../include/NodeRBT.hpp"

#include <string>
#include <iostream>
#include <chrono>

using namespace std::chrono;

void run_RBT(){
    RBT T;

    std::string input;
    int k;
    std::string v;
    do {
        std::cin >> input;
        switch (input[0]) {
            case 'i':
            {
                std::cin >> k;
                std::cin >> v;
                NodeRBT* x = new NodeRBT(k,v);
                T.insert(x);
                break;
            }
            case 's':
            {
                T.show(T.get_root());
                std::cout << '\n';
                break;
            }
            case 'f':
            {
                std::cin >> k;
                std::cout << T.find_value(k) << '\n';
                break;
            }
            case 'c':
            {
                T.clear(T.get_root());
                break;
            }
            case 'p':
            {
                T.print_info(T.get_root());
                break;
            }
            case 'e':
                exit(0);
            default:
                std::cout << "Comando non riconosciuto\n"; 
                break;
        }
    } while(true);
}

void run_BST(){
    BST T;

    std::string input;
    int k;
    std::string v;
    /*
    for (int i = 0; i < 10000; i++)
    {
        Node* x = new Node(input_keys[i], "a");
        T.insert(x);
    }
    */
    do {
        std::cin >> input;
        switch (input[0]) {
            case 'i':
            {
                std::cin >> k;
                std::cin >> v;
                Node* z = new Node(k, v);
                T.insert(z);
                break;
            }
            case 's':
            {
                T.show(T.get_root());
                std::cout << '\n';
                break;
            }
            case 'r':
            {
                std::cin >> k;
                T.remove(k);
                break;
            }
            case 'f':
            {
                std::cin >> k;
                //auto BST_t1_find = steady_clock::now();
                std::string value = T.find_value(k);
                //auto BST_t2_find = steady_clock::now();
                //auto calc = duration_cast<duration<double>>(BST_t2_find - BST_t1_find).count();
                //calc = calc * 1000;
                //std::cout << calc << '\n';
                std::cout << value << '\n';
                break;
            }
            case 'c':
            {
                T.clear(T.get_root());
                break;
            }
            case 'e':
                exit(0);
            case 'p':
            {
                T.print_info(T.get_root());
                break;
            }
            default:
                std::cout << "Comando non riconosciuto\n"; 
                break;
        }
    } while(true);
}

void run_AVL(){
    AVL T;
    
    std::string input;
    int k;
    std::string v;
    /*
    for (int i = 0; i < 10000; i++)
    {
        Node* x = new Node(input_keys[i], "a");
        T.insert_helper(T.get_root(), nullptr, x);
    }
    */
    do{ 
        std::cin >> input;
        switch(input[0]){
            case 'i':
            {
                std::cin >> k;
                std::cin >> v;
                Node* y = new Node(k, v);
                T.insert_helper(T.get_root(), nullptr, y);
                break;
            }/*
            case 'r':
            {
                std::cin >> k;
                T.remove(k);
                break;
            }*/
            case 'c':
            {
                T.clear(T.get_root());
                break;
            }
            case 'f':
            {
                std::cin >> k;
                // auto AVL_t1_find = steady_clock::now();
                std::string value_of_node = T.find_value(k);
                // auto AVL_t2_find = steady_clock::now();
                // auto calc = duration_cast<duration<double>>(AVL_t2_find - AVL_t1_find).count();
                // calc = calc * 1000;
                // std::cout << calc << '\n';
                std::cout << value_of_node << '\n';
                break;
            }
            case 's':
            {
                T.show(T.get_root());
                std::cout << '\n';
                break;
            }
            case 'e':
                exit(0);
            case 'p':
            {
                T.print_info(T.get_root());
                break;
            }
            default:
                std::cout << "Comando non riconosciuto\n";
                break;
        }
    } while(true);
}

int main()
{
    core();
} 

/*


int main(){
    std::string type_of_tree;
    std::cout << "Inserire il tipo di struttura che si desidera utilizzare (BST - AVL) : \n";
    std::cin >> type_of_tree;
    //generate_random_nodes(10000);
    switch(type_of_tree[0]) {
        case 'B' :
            std::cout << "Hai scelto BST.\n";
            run_BST();
            break;
        case 'A' :
            std::cout << "Hai scelto AVL.\n";
            run_AVL();
            break;
        default :
            std::cout << "Non hai inserito una delle due opzioni. Uscita dal programma.\n";
            exit(0);
    }
}

*/