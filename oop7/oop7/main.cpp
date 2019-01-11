#include <cstdlib>
#include <iostream>
#include <memory>

#include "Figure.hpp"
#include "Triangle.hpp"
#include "Octagon.hpp"
#include "Square.hpp"
#include "TTree.hpp"
#include "TList.hpp"
#include "IRemoveCriteriaByValue.hpp"
#include "IRemoveCriteriaAll.hpp"

void help(){
    std::cout << "-----MENU----\n";
    std::cout << "1 - add the octagon\n";
    std::cout << "2 - add the triangle\n";
    std::cout << "3 - add the square\n";
    std::cout << "4 - delete the element by value\n";
    std::cout << "5 - delete the element by type\n";
    std::cout << "6 - print the tree\n";
    std::cout << "7 - help\n";
    std::cout << "0 - exit\n";
}

int main(int argc, char** argv) {
    TBinaryTree<TList<Figure>,Figure> tree;
    IRemoveCriteriaBySquare<Figure> criteria(0);
    IRemoveCriteriaAll<Figure> criteriaAll(0);
    
    size_t check, a, b, c;
    
    std::shared_ptr<Figure> tmp;
    
    help();
    while (1) {
        std::cout << "\nParameter: ";
        std::cin >> check;
        switch (check) {
            case 1:
                std::cout << "Enter the ocragon: ";
                std::cin >> a;
                tmp = std::make_shared<Octagon>(a);
                tree.InsertSubitem(tmp);
                break;
            case 2:
                std::cout << "Enter the triangle: ";
                std::cin >> a >> b >> c;
                tmp = std::make_shared<Triangle>(a, b, c);
                tree.InsertSubitem(tmp);
                break;
            case 3:
                std::cout << "Enter the square: ";
                std::cin >> a;
                tmp = std::make_shared<FSquare>(a);
                tree.InsertSubitem(tmp);
                break;
            case 4:
                std::cout << "Enter the value: ";
                std::cin >> a;
                criteria = a;
                tree.RemoveSubitem(&criteria);
                break;
            case 5:
                std::cout << "Enter the type(1 - octagon, 2 - triangle, 3 - square): ";
                std::cin >> a;
                criteriaAll = a;
                tree.RemoveSubitem(&criteriaAll);
                break;
            case 6:
                std::cout << tree;
                break;
            case 7: help(); break;
            case 0: return 0;
            default: break;
        }
    }
    return 0;
}
