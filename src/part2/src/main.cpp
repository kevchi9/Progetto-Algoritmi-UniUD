#include <string>
#include <iostream>
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"

void run_BST(){
    BST T;

    std::string input;
    int k;
    std::string v;
    Node* x = T.get_root();
    do {
        std::cin >> input;
        switch (input[0]) {
            case 'i':
            {
                std::cin >> k;
                std::cin >> v;
                Node* z = new Node(k, v);
                T.BST_insert(z);
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
                T.BST_remove(k);
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
                T.clear(x);
                break;
            }
            case 'e':
                exit(0);
            case 'p':
            {
                T.print_info(x);
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

    do{ 
        std::cin >> input;
        switch(input[0]){
            case 'i':
            {
                std::cin >> k;
                std::cin >> v;
                Node* y = new Node(k, v);
                T.AVL_insert(y);
                break;
            }
            case 'r':
            {
                std::cin >> k;
                T.AVL_remove(k);
                break;
            }
            case 'c':
            {
                T.clear(T.get_root());
                break;
            }
            case 'f':
            {
                std::cin >> k;
                std::cout << T.find_value(k) << '\n';
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

int main(){
    std::string type_of_tree;
    std::cout << "Inserire il tipo di struttura che si desidera utilizzare (BST - AVL) : \n";
    std::cin >> type_of_tree;
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