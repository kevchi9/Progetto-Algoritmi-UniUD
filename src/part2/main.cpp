#include <string>
#include <iostream>
#include "Node.hpp"
#include "BST.hpp"
#include "AVL.hpp"

void run_BST(){
    BST* T = new BST();
    std::string input;
    int k;
    std::string v;
    Node* root = nullptr;
    do {
        std::cin >> input;
        switch (input[0]) {
            case 'i':
                std::cin >> k;
                std::cin >> v;
                if (root == nullptr){
                    root = new Node(k, v);
                } else {
                    T->BST_insert(root, k, v);
                }
                break;
            case 's':
                T->show(root);
                std::cout << '\n';
                break;
            case 'r':
                std::cin >> k;
                root = T->BST_remove(root,k);
                break;
            case 'f':
                std::cin >> k;
                T->find_value(root,k);
                break;
            case 'c':
                root = T->clear(root);
                break;
            case 'e':
                exit(0);
            default:
                std::cout << "Comando non riconosciuto\n"; 
                break;
        }
    } while(true);
}

void run_AVL(){
    AVL* T = new AVL();
    std::string input;
    int k;
    std::string v;
    Node* root = nullptr;
    do{
        std::cin >> input;
        switch(input[0]){
            case 'i':
                std::cin >> k;
                std::cin >> v;
                if(root != nullptr){
                    root = T->AVL_insert(root, k, v);
                } else {
                    root = new Node(k, v);
                }
                break;
            case 'r':
                std::cin >> k;
                std::cout << "Ancora da implementare\n";
                root = T->AVL_remove(root, k);
                break;
            case 'c':
                root = T->clear(root);
            case 'f':
                std::cin >> k;
                T->find_value(root, k);
                break;
            case 's':
                T->show(root);
                break;
            case 'e':
                exit(0);
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

