#include <cstdlib>
#include <iostream>
#include "Triangle.h"
#include "TBinaryTree.h"
#include <random>

void help(){
    std::cout << "-----MENU----\n";
    std::cout << "1 - add the figure\n";
    std::cout << "2 - sort\n";
    std::cout << "3 - sort parallel\n";
    std::cout << "4 - print the tree\n";
    std::cout << "5 - help\n";
    std::cout << "0 - exit\n";
}

int main(int argc, char** argv) {
    
    TBinaryTree<Triangle> tree;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 7);
    
    int check, a, index;
    
    help();
    while (1) {
        std::cout << "\nParameter: ";
        std::cin >> check;
        switch (check) {
            case 1:
                std::cout << "Enter the triangle: ";
                std::cin >> a;
                index = distribution(generator);
                tree.push(new Triangle(a, a, a), index);
                break;
            case 2:
                std::cout << "-----SORT-----\n";
                tree.sort();
                std::cout << "-----DONE-----\n";
                break;
            case 3:
                std::cout << "-----SORT-----\n";
                tree.sort_parallel();
                std::cout << "-----DONE-----\n";
                break;
            case 4:
                std::cout << tree << std::endl;
                break;
            case 5: help(); break;
            case 0: return 0;
            default: break;
        }
    }
    
//    for (int i = 0; i < 7; i++) {
//        int side = distribution(generator);
//        int index = distribution(generator);
//        stack.push(new Triangle(side, side, side), index);
//    }
//
//    std::cout << stack << std::endl;
//
//    std::cout << "Sort -------------" << std::endl;
//
////    stack.sort();
//    stack.sort_parallel();
//    std::cout << "Done -------------\n" << std::endl;
//
//    std::cout << stack << std::endl;
    
    return 0;
}
