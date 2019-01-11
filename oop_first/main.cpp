#include <cstdlib>
#include <iostream>
#include <memory>
#include "Figure.h"
#include "Square.h"
#include "Octagon.h"
#include "Triangle.h"
#include "BinaryTree.h"
#include "LinkedList.h"
#include "Tallocationblock.h"

void help(){
    std::cout << "-----MENU----\n";
    std::cout << "1 - add the octagon\n";
    std::cout << "2 - add the square\n";
    std::cout << "3 - add the triangle\n";
    std::cout << "4 - delete the element\n";
    std::cout << "5 - print the tree\n";
    std::cout << "6 - exit\n";
    std::cout << "0 - help\n";
}

int main(int argc, char** argv) {

     std::shared_ptr<Figure> tmp;

     size_t x;
     char check = '\0';
    
     BinaryTree<Figure> tree;
    
     help();
     while (1) {
         std::cout << "\nParameter: ";
         std::cin >> check;
         switch (check) {
             case '1':
                 std::cout << "Enter the ocragon: ";
                 tmp = std::make_shared<Octagon>(std::cin);
                 std::cout << "Enter the smth number: ";
                 std::cin >> x;
                 tree.push(tmp, x);
                 break;
             case '2':
                 std::cout << "Enter the square: ";
                 tmp = std::make_shared<FSquare>(std::cin);
                 std::cout << "Enter the smth number: ";
                 std::cin >> x;
                 tree.push(tmp, x);
                 break;
             case '3':
                 std::cout << "Enter the triangle: ";
                 tmp = std::make_shared<Triangle>(std::cin);
                 std::cout << "Enter the smth number: ";
                 std::cin >> x;
                 tree.push(tmp, x);
                 break;
             case '4':
                 std::cout << "Enter the number of figure: ";
                 std::cin >> x;
                 tree.pop(x);
                 break;
             case '5':
                 //for(auto i : tree)  std::cout << *i << std::endl;
                 break;
             case '6':
                 return 0;
             case '0':
                 help();
                 break;
             default:
                 std::cout << "Wrong input!!\n";
                 break;
         }
     }
    return 0;
}

