#include "../include/core.hpp"
#include "../include/Node.hpp"
#include "../include/AVL.hpp"
#include "../include/BST.hpp"
#include "../include/RBT.hpp"
#include "../include/NodeRBT.hpp"

#include <string>
#include <iostream>

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
    Node* x = T.get_root();
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
                T.insert(y);
                break;
            }
            case 'r':
            {
                std::cin >> k;
                T.remove(k);
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
    //main_BST();
    run_RBT();
}

/*

insert 3 three
insert 7 seven
insert 9 nine
insert 0 zero
insert 12 twelve
show
find 3

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