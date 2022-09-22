#include <iostream>

#include "splay_tree.h"

enum operation {INSERT, FIND, REMOVE};

int main(void) {
    SplayTree* tree = new SplayTree();
    std::string input;

    bool get_op_flag = true;
    operation op;
    while (true) {
        if (get_op_flag) {
            std::cout << "Operation? (insert, find, remove, print, quit): ";
        } else {
            std::cout << "Key? (int): ";
        }
        std::cin >> input;

        if (input == "quit" || input == "q") {
            break;
        }

        if (get_op_flag) {
            get_op_flag = false;
            if (input == "insert" || input == "i")
                op = INSERT;
            else if (input == "find" || input == "f")
                op = FIND;
            else if (input == "remove" || input == "r")
                op = REMOVE;
            else if (input == "print" || input == "p") {
                tree->pretty_print();
                get_op_flag = true;
            }
            else {
                std::cout << "Invalid input" << std::endl;
                get_op_flag = true;
            }
        } else {
            get_op_flag = true;
            int key = std::stoi(input);
            switch (op) {
                case INSERT:
                    tree->insert(key);
                    tree->pretty_print();
                    break;
                case FIND:
                    std::cout << (tree->find(key) ? "True" : "False") << std::endl;
                    tree->pretty_print();
                    break;
                case REMOVE:
                    tree->remove(key);
                    tree->pretty_print();
                    break;
                
            }
        }

    }
    
    
}





