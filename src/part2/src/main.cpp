#include "../include/core.hpp"
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include "../include/RBT.hpp"
#include "../include/NodeRBT.hpp"

#include <string>
#include <iostream>

/*
insert 19 nineteen
insert 9 nine
insert 1 one
insert 7 seven
insert 12 twelve
insert 13 thirteen
insert 16 sixteen
*/

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
                T.RBT_Insert(k, v);
                break;
            }
            case 's':
            {
                T.RBT_Show(T.get_root());
                std::cout << '\n';
                break;
            }
            case 'f':
            {
                std::cin >> k;
                std::cout << T.RBT_Find(k)->get_value() << '\n';
                break;
            }
            case 'c':
            {
                T.RBT_Clear(T.get_root());
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


int main(){
    //main_BST();
    run_RBT();
}

/**
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
*/